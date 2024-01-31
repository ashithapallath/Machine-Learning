#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

// Random integer array generation
std::vector<int> genRandArray(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100; 
    }
    return arr;
}

// Sum of elements in a partition
int sumPart(const std::vector<int>& arr, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; ++i) {
        sum += arr[i];
    }
    return sum;
}

// Search for a key element in a partition
bool searchPart(const std::vector<int>& arr, int start, int end, int key) {
    for (int i = start; i < end; ++i) {
        if (arr[i] == key) {
            return true;
        }
    }
    return false;
}

// Threaded sum computation
void threadSum(const std::vector<int>& arr, int numThreads) {
    int n = arr.size();
    int numsPerThread = n / numThreads;
    int remainder = n % numThreads;

    std::vector<std::thread> threads;
    std::vector<int> threadSums(numThreads, 0);

    // Create threads
    for (int i = 0; i < numThreads; ++i) {
        int start = i * numsPerThread;
        int end = (i + 1) * numsPerThread;
        if (i == numThreads - 1) {
            end += remainder;
        }

        // Create a thread and pass the sumPart function along with the range of numbers
        threads.emplace_back([&, start, end, i]() {
            threadSums[i] = sumPart(arr, start, end);
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Calculate the final sum
    int finalSum = 0;
    for (int sum : threadSums) {
        finalSum += sum;
    }

    std::cout << "Threaded Sum: " << finalSum << std::endl;
}

// Threaded search computation
void threadSearch(const std::vector<int>& arr, int numThreads, int key) {
    int n = arr.size();
    int numsPerThread = n / numThreads;
    int remainder = n % numThreads;

    std::vector<std::thread> threads;
    std::vector<bool> threadResults(numThreads, false);

    // Create threads
    for (int i = 0; i < numThreads; ++i) {
        int start = i * numsPerThread;
        int end = (i + 1) * numsPerThread;
        if (i == numThreads - 1) {
            end += remainder;
        }

        // Create a thread and pass the searchPart function along with the range of numbers
        threads.emplace_back([&, start, end, i]() {
            threadResults[i] = searchPart(arr, start, end, key);
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Check if the key is found in any partition
    bool keyFound = false;
    for (bool result : threadResults) {
        if (result) {
            keyFound = true;
            break;
        }
    }

    if (keyFound) {
        std::cout << "Key found in the array." << std::endl;
    } else {
        std::cout << "Key not found in the array." << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int size, numThreads;

    std::cout << "Enter array size: ";
    std::cin >> size;

    std::cout << "Enter number of threads: ";
    std::cin >> numThreads;

    // Generate a random array
    std::vector<int> arr = genRandArray(size);

    // Measure execution time for threaded sum
    auto startThreadedSum = std::chrono::high_resolution_clock::now();
    threadSum(arr, numThreads);
    auto endThreadedSum = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> threadedSumDuration = endThreadedSum - startThreadedSum;
    std::cout << "\nNumber of Threads: " << numThreads << std::endl;
    std::cout << "Threaded Sum | Execution Time: " << threadedSumDuration.count() << " seconds\n";

    // Measure execution time for threaded search
    int key = arr[rand() % size];
    auto startThreadedSearch = std::chrono::high_resolution_clock::now();
    threadSearch(arr, numThreads, key);
    auto endThreadedSearch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> threadedSearchDuration = endThreadedSearch - startThreadedSearch;
    std::cout << "Threaded Search for key " << key << " | Execution Time: " << threadedSearchDuration.count() << " seconds\n";

    return 0;
}
