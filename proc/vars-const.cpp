#include <iostream>

int main()
{
  const auto pi = 3.14159265359;

  double radius;
  std::cout << "Enter the circle's radius: ";
  std::cin >> radius;

  const auto area = radius * radius * pi; // radius * radius = radius squared
  const auto diameter = 2 * radius;
  const auto perimeter = diameter * pi;

  std::cout << "r = " << radius << " ==> "
            << "d = " << diameter
            << ", A = " << area
            << ", P = " << perimeter << "\n";
}
