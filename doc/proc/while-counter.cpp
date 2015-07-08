#include <iostream>

int main()
{
    unsigned n;
    std::cout << "Enter number of iterations: ";
    std::cin >> n;

    // The counter loop:
    auto i = 0u; // u: unsigned suffix
    while (i < n) {
        std::cout << "Iteration with i = " << i << '\n';
        i += 1;
    }
    std::cout << "Loop left with i = " << i << '\n';
}
