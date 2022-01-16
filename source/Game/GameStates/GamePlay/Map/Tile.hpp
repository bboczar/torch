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
        Land
    };

    Type type;
    unsigned size;
    sf::Vector2i centre;
    bool occupied;
};

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game