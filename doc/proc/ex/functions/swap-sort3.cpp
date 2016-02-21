#include <iostream>

void swap(int& a, int& b)
{
    auto original_a = a;
    a = b;
    b = original_a;
}

int main()
{
    int a, b, c;
    std::cout << "Enter three numbers: ";
    std::cin >> a >> b >> c;

    // Make sure a is the smallest number:
    if (a > b)
        swap(a, b);
    if (a > c)
        swap(a, c);

    // Make sure that b and c are in the correct order:
    if (b > c)
        swap(b, c);

    std::cout << "Sorted: " << a << ' ' << b << ' ' << c << '\n';
}
