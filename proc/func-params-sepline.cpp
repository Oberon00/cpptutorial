#include <iostream>

void print_sepline(char sep_char, unsigned sep_len)
{
    for (auto i = 0u; i < sep_len; ++i)
        std::cout << sep_char;
    std::cout << '\n';
}

int main()
{
    std::cout << "First separator line:\n";
    print_sepline('=', 60);
    std::cout << "Second separator line:\n";
    print_sepline('_', 80 / 4);

    char sepline_char;
    std::cout << "Enter separator character: ";
    std::cin >> sepline_char;

    unsigned sepline_length;
    std::cout << "Enter length of separator line: ";
    std::cin >> sepline_length;

    std::cout << "Your custom seperator line:\n";
    print_sepline(sepline_char, sepline_length);

    std::cout << "Double the length:\n";
    print_sepline(sepline_char, sepline_length * 2);
}
