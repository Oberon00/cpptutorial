#include <iostream>

int main()
{
    int x;
    std::cout << "Enter x: ";
    if (!(std::cin >> x)) {
        std::cout << "E: Invalid number.\n";
        return 1;
    }

    if (x == 0) {
        std::cout << "E: x is zero.\n";
        return 1;
    }

    std::cout << "Reciprocal: " << 1 / x << '\n';
    //return 0; // Inserted automatically by the compiler.
}
