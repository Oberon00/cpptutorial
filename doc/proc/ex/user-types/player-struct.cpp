#include <iostream>

struct Player {
    int x, y;
    int points;
};

void draw_player(Player player)
{
    std::cout
        << "Player at " << player.x << "," << player.y
        << " with " << player.points << " points.\n";
}

void next_round(unsigned& game_round)
{
    ++game_round;
    std::cout << "Round " << game_round << ":\n";
}

int main()
{
    auto game_round = 0u;
    Player player_a = {}, player_b = {};

    next_round(game_round);
    draw_player(player_a);
    draw_player(player_b);

    next_round(game_round);
    player_a.x += 5; // Move player to the right a bit.
    draw_player(player_a);
}
