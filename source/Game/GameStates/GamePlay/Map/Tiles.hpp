#pragma once

#include <optional>
#include <vector>

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Map/Tile.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

using MaybeLocation = std::optional<sf::Vector2i>;

class Tiles
{
public:
    Tiles();
    MaybeLocation requestBuildLocation(const sf::Vector2i& point);
    void markOccupied(const sf::Vector2i& point);
    void draw(sf::RenderWindow& window) const;

private:
    void setDefaultTiles();
    Tile& getTileIncluding(const sf::Vector2i& point);
    bool tileIncludes(const Tile& tile, const sf::Vector2i& point) const;
    void drawTile(const Tile& tile, sf::RenderWindow& window) const;

    std::vector<Tile> tiles_;
};

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game