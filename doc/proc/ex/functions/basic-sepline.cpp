#include <iostream>

void print_sepline()
{
    const auto sep_char = '-';
    const auto sep_len = 60u;

    for (auto i = 0u; i < sep_len; ++i)
        std::cout << sep_char;
    std::cout << '\n';
}

int main()
{
    std::cout << "Above separator lines.\n";
    print_sepline();
    std::cout << "Between separator lines.\n";
    print_sepline();
    std::cout << "Below separator lines.\n";
}
