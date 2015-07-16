#include <iostream>

struct Player {
    int x, y;
    int points;
};

void print_player(Player player)
{
    std::cout << player.x << ',' << player.y << ": " << player.points << '\n';
}

int main()
{
    Player player = {5, 3, 100};
    print_player(player);
    player = {1, 2, 3};
    print_player(player);

    Player player_b = {5};
    print_player(player_b);

    print_player({10, 7, 250});
}
