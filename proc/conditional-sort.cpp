#include <iostream>

int main()
{
    int a;
    int b;
    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;
    if (a > b) {
        auto original_a = a;
        a = b;
        b = original_a;
    } else {
        std::cout << "Numbers already sorted.\n";
    }
    std::cout << "Smaller number: " << a << '\n';
    std::cout << "Bigger number: " << b << '\n';
}
