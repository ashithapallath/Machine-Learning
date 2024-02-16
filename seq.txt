#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

void gen(int a[], int b) {
    for (int c = 0; c < b; ++c) {
        a[c] = rand() % 100;
    }
}

int calc(int a[], int b) {
    int c = 0;
    for (int d = 0; d < b; ++d) {
        c += a[d];
    }
    return c;
}

int main() {
    srand(time(0));
    int e;
    std::cout << "Enter the size of the array: ";
    std::cin >> e;
    int *f = new int[e];
    gen(f, e);
    auto g = std::chrono::high_resolution_clock::now();
    int h = calc(f, e);
    auto i = std::chrono::high_resolution_clock::now();
    double j = std::chrono::duration<double, std::milli>(i - g).count();
    std::cout << "Sum of elements: " << h << std::endl;
    std::cout << "Execution time: " << j << " milliseconds" << std::endl;
    delete[] f;
    return 0;
}
