#include <iostream>

int main()
{
    unsigned width;
    std::cout << "width: ";
    std::cin >> width;

    unsigned height;
    std::cout << "height: ";
    std::cin >> height;

    std::cout << '\n';

    const auto brush_char = '#';

    for (auto y = 0u; y < height; ++y) {
        for (auto x = 0u; x < width; ++x)
            std::cout << brush_char;
        std::cout << '\n';
    }
}
