#include <iostream>

int main()
{
    std::cout << "Enter numbers. Enter a letter to quit.\n";
    double n;
    while (std::cin >> n) {
        std::cout << "Negated: " << -n << '\n';
        std::cout << "Doubled: " << 2 * n << '\n';

        if (n != 0)
            std::cout << "Reciprocal: " << 1 / n << '\n';
    }
}
