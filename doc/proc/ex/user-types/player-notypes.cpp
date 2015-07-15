#include <iostream>

void draw_player(int player_x, int player_y, int player_points)
{
    std::cout
        << "Player at " << player_x << "," << player_y
        << " with " << player_points << " points.\n";
}

void next_round(unsigned& game_round)
{
    ++game_round;
    std::cout << "Round " << game_round << ":\n";
}

int main()
{
    auto game_round = 0u;
    auto player_a_x = 0, player_a_y = 0, player_a_points = 0;
    auto player_b_x = 0, player_b_y = 0, player_b_points = 0;

    next_round(game_round);
    draw_player(player_a_x, player_a_y, player_a_points);
    draw_player(player_b_x, player_b_y, player_b_points);

    next_round(game_round);
    // Move player a right a bit:
    player_a_x += 5;
    draw_player(player_a_x, player_a_y, player_a_points);
}
