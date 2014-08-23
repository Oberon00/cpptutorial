#include <iostream>

int main()
{
    int a, b, c;
    std::cout << "Enter three numbers: ";
    std::cin >> a >> b >> c;

    // Make sure a is the smallest number:
    if (a > b) { // Swap a and b
        auto original_a = a;
        a = b;
        b = original_a;
    }
    if (a > c) { // Swap a and c
        auto original_a = a;
        a = c;
        c = original_a;
    }

    // Make sure that b and c are in the correct order:
    if (b > c) {
        auto original_b = b;
        b = c;
        c = original_b;
    }

    std::cout << "Sorted: " << a << ' ' << b << ' ' << c << '\n';
}
