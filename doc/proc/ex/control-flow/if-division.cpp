#include <iostream>

int main()
{
    double dividend;
    std::cout << "Enter dividend: ";
    std::cin >> dividend;

    double divisor;
    std::cout << "Enter divisor: ";
    std::cin >> divisor;

    if (divisor != 0)
        std::cout << "Result: " << dividend / divisor << "\n";

    std::cout << "Good bye!\n";
}
