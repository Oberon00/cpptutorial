#include <iostream>

int main()
{
    // Get numbers from user:
    int x;
    std::cout << "Enter x: ";
    std::cin >> x;
    int y;
    std::cout << "Enter y: ";
    std::cin >> y;

    std::cout << "\n";

    // Test equality:
    std::cout << "x == y? " << (x == y) << "\n";
    std::cout << "x != y? " << (x != y) << "\n";

    std::cout << "\n";

    // Print relation table:
    std::cout << "Relation: <   <=  >   >=\n";
    std::cout << "------------------------\n";
    std::cout << "x OP y? | "
              << (x < y) << "   " << (x <= y) << "   "
              << (x > y) << "   " << (x >= y) << "\n";
    std::cout << "y OP x? | "
              << (y < x) << "   " << (y <= x) << "   "
              << (y > x) << "   " << (y >= x) << "\n";
}
