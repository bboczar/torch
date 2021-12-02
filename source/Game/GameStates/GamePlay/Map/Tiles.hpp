#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

using MaybeLocation = std::optional<sf::Vector2i>;

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

class Tiles
{
public:
    Tiles();
    MaybeLocation requestBuildLocation(const sf::Vector2i& point);
    void markOccupied(const sf::Vector2i& point);

private:
    Tile& getTileIncluding(const sf::Vector2i& point);
    bool tileIncludes(const Tile& tile, const sf::Vector2i& point) const;
    std::vector<Tile> tiles_;
};

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game