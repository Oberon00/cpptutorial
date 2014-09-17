#include <iostream>

void minmax(int x, int y, int& min, int& max)
{
    if (x < y) {
        min = x;
        max = y;
    } else {
        min = y;
        max = x;
    }
}

int main()
{
    int a = 42, b = 14;
    int lo, hi;
    minmax(a, b, lo, hi);
    std::cout << "Lower: " << lo << '\n';
    std::cout << "Higher: " << hi << '\n';
}
