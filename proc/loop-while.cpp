#include <iostream>

int main()
{
    int hit_points;
    std::cout << "Enter the robot's initial hit points:";
    std::cin >> hit_points;

    while (hit_points > 0) {
        int damage;
        std::cout << "Enter the damage dealt: ";
        std::cin >> damage;
        hit_points -= damage;

        std::cout << "Remaining hit points: " << hit_points << "\n";
    }
    std::cout << "The robot is destroyed.\n";
}
