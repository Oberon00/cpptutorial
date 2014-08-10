#include <iostream>

int main()
{
    int age; // Age in years
    std::cout << "How old are you? ";
    std::cin >> age;

    if (age < 16) {
        int height; // Height in centimetre
        std::cout << "How tall are you? ";
        std::cin >> height;

        if (height < 160)
            std::cout << "Sorry, you are not tall enough.\n";
        else
            std::cout << "You are tall enough to take a ride!\n";
    } else {
        std::cout << "You are old enough to take a ride!\n;";
    }
}
