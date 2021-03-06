#include <iostream>

int main()
{
    auto pi = 3.14159265359;

    double radius;
    std::cout << "Enter the circle's radius: ";
    std::cin >> radius;

    auto area = radius * radius * pi; // radius * radius = radius squared
    auto diameter = 2 * radius;
    auto perimeter = diameter * pi;

    std::cout << "r = " << radius << " ==> "
              << "d = " << diameter
              << ", A = " << area
              << ", P = " << perimeter << "\n";
}
