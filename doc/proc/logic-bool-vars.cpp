#include <iostream>

int main()
{
    std::cout << "true : " << true  << "\n";
    std::cout << "false: " << false << "\n";
    std::cout << "\n";

    auto is_valid = true; // is_valid gets the type bool.
    std::cout << "Valid? " << is_valid << "\n";
    is_valid = false;
    std::cout << "Still valid? " << is_valid << "\n";
    std::cout << "\n";

    bool some_bool;
    std::cout << "Enter a boolean value (0 for false, 1 for true): ";
    std::cin >> some_bool;
    std::cout << "You entered " << some_bool << ".\n";
}
