#include <iostream>

int main()
{
    const auto max_number_count = 10;
    const auto target_sum = 256;

    std::cout << "Enter number:\n";
    auto sum = 0;
    for (auto i = 0; i < max_number_count && sum < target_sum; ++i) {
        int n;
        std::cin >> n;
        sum += n;

        if (sum < target_sum)
            std::cout << "Sum not reached yet.\n";
    }
    if (sum >= target_sum)
        std::cout << "Target sum " << target_sum << " reached.\n";

    std::cout << "Final sum: " << sum << '\n';
}
