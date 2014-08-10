#include <iostream>

int main()
{
    int x;
    std::cout << "Enter x: ";
    std::cin >> x;

    if (x >= 0)
        if (x <= 100)
            std::cout << "x is between 0 and 100.\n";
    else
        std::cout << "x is negative.\n";
}
