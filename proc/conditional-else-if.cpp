#include <iostream>

int main()
{
    int x;
    std::cout << "Enter a number: ";
    std::cin >> x;

    if (x < 0)
        std::cout << "x is negative. (-)\n";
    else if (x > 0)
        std::cout << "x is positive. (+)\n";
    else
        std::cout << "x is zero. (0)\n";
}
