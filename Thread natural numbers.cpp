#include <iostream>
#include <thread>

void printNumbers(int n) {
    for (int i = 1; i <= n; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;

    // Get the value of n from the user
    std::cout << "Enter the value of n: ";
    std::cin >> n;

    // Create a thread and pass the printNumbers function with n as an argument
    std::thread t(printNumbers, n);

    // Join the thread to the main thread
    t.join();

    return 0;
}
