#include <iostream>

int g_sum = 0;

void add_to_sum(int x)
{
    g_sum += x;
}

void double_sum()
{
    g_sum *= 2;
}

int main()
{
    add_to_sum(32);
    double_sum();
    add_to_sum(12);
    std::cout << "sum = " << g_sum << '\n';
}
