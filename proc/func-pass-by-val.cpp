#include <iostream>

void f(int y)
{
    std::cout << "entered f: " << y << '\n';
    y = 23;
    std::cout << "leaving f: " << y << '\n';
}

void g(int x)
{
    std::cout << "entered g: " << x << '\n';
    x = 23;
    std::cout << "leaving g: " << x << '\n';
}

int main()
{
    auto x = 42;
    f(x);
    std::cout << "after f: " << x << '\n';
    g(x);
    std::cout << "after g: " << x << '\n';
}
