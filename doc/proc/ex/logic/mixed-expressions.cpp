#include <iostream>

int main()
{
    const auto monster_level = 12;

    int player_level;
    std::cout << "Enter your level: ";
    std::cin >> player_level;
    
    int sword_strength;
    std::cout << "Enter your sword's strength: ";
    std::cin >> sword_strength;

    bool is_player_in_god_mode;
    std::cout << "Are you a cheater? ";
    std::cin >> is_player_in_god_mode;

    auto winning = is_player_in_god_mode
                   || player_level + sword_strength > monster_level;

    std::cout << "You beat the monster: " << winning << "\n";
}
