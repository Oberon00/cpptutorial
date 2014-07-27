#include <iostream>

int main()
{
  double pi = 3.14159265359;

  int radius = 3;

  double area = radius * radius * pi; // radius * radius = radius squared
  double diameter = 2 * radius;
  double perimeter = diameter * pi;

  std::cout << "r = " << radius << " ==> "
            << "d = " << diameter
            << ", A = " << area
            << ", P = " << perimeter << "\n";
}
