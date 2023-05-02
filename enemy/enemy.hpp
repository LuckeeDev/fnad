#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include <SFML/Graphics>

namespace fnad
{
    enum class Status
    {
        susceptible,
        infectious,
        removed
    };

    enum class Floor
    {
        underground,
        ground,
        first,
        second,
        roof
    };

    struct Position
    {
        sf::Vector2f position;
        int floor;
    };

    class Enemy
    {
    private:
        Status status_{Status::susceptible};
        Position position_;

    public:
        void evolve();
    };
}

#endif