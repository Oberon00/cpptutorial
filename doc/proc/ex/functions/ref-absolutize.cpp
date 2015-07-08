#include <iostream>

void absolutize(int& v)
{
    if (v < 0)
        v = -v; // Make v positive
}

int main()
{
    int x;
    std::cout << "x: ";
    std::cin >> x;

    absolutize(x);
    std::cout << "absolutized x: " << x << '\n';
}
