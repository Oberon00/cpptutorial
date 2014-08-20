#include <iostream>

int main()
{
    double value;
    std::cout << "Enter initial value: ";
    std::cin >> value;

    double d; // difference
    do {
        std::cout << "Enter value to add or 0 to exit: ";
        std::cin >> d;
        value += d; // Addition of 0 (exit) does not change the value.
        std::cout << "Current value: " << value << "\n";
    } while (d != 0);
}
