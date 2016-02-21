#include <iostream>

struct Point {
    int x;
    int y;
};

struct Player {
public:
    int x() const { return m_position.x; }
    void set_x(int x_) { m_position.x = x_; } 

    int y() const { return m_position.y; }
    void set_y(int y_) { m_position.y = y_; }

    int n_points() const { return m_n_points; }
    void set_n_points(int n_points_) { m_n_points = n_points_; }

    Point position() const { return m_position; }

private:
    Point m_position;
    int m_n_points;
};

void draw_player(Player const& player)
{
    std::cout
        << "Player at " << player.x() << "," << player.y()
        << " with " << player.n_points() << " points.\n";
}

int main()
{
    Player player;
    player.set_x(1);
    player.set_y(2);
    player.set_n_points(10);

    draw_player(player);
}
