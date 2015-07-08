#include <iostream>

int main()
{
    unsigned height;
    std::cout << "Enter the pyramid's height: ";
    std::cin >> height;

    bool centered;
    std::cout << "Should the tip be centered (0/1)? ";
    std::cin >> centered;


    auto block_factor = 1u;
    if (centered)
        block_factor = 2u;

    auto block_char = '#';

    for (auto y = 0u; y < height; ++y) {
        if (centered) {
            // Print spaces in front:
            for (auto i = 0u; i < height - 1u - y; ++i)
                std::cout << ' ';
        }

        // Print blocks:
        for (auto i = 0u; i < y * block_factor + 1u; ++i)
            std::cout << block_char;

        std::cout << '\n';
    }
}
