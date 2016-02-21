#include <iostream>

struct Point {
    int x;
    int y;
};

struct Player {
    Point position;
    int n_points;

    void draw() const
    {
        std::cout
            << "Player at " << position.x << "," << position.y
            << " with " << n_points << " points.\n";
    }
};

int main()
{
    Player player_a = {}, player_b = {{2, 3}, 1};
    player_a.draw();
    player_b.draw();
}
