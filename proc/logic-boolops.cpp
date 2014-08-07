#include <iostream>

int main()
{
    auto has_armor = false;
    auto has_sword = true;

    std::cout << "In need of equipment: " << !(has_armor || has_sword) << "\n";

    bool quest_complete;
    std::cout << "Have you found the potion yet? ";
    std::cin >> quest_complete;

    bool is_member;
    std::cout << "Are you a member of the guild? ";
    std::cin >> is_member;

    auto paid_bribe = false;
    std::cout << "Ready for boss fight: "
              << (has_armor && has_sword && quest_complete) << "\n";
    std::cout << "Gets offered guild items: "
              << (is_member && (quest_complete || paid_bribe)) << "\n";
}
