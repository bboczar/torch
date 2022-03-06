#pragma once

#include <SFML/Graphics.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

struct Tile
{
    enum class Type
    {
        Path,
        Land,
        Start,
        Finish
    };

    Type type;
    unsigned size;
    sf::Vector2i centre;
    bool occupied;
    sf::RectangleShape shape;
};

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game