#include <iostream>

int main()
{
    auto const correct_pin = 1234;

    unsigned pin;
    std::cout << "Enter PIN: ";
    std::cin >> pin;
    std::cout << (pin == correct_pin ? "OK" : "Invalid!") << '\n';
}
