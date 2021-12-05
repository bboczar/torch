#include <Game/GameStates/GamePlay/Map/Map.hpp>

#include <cassert>
#include <fstream>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

Map::Map()
{
    assert(backgroundTexture_.loadFromFile("resources/map.png") && "Missing background texture");
    background_.setTexture(backgroundTexture_);
}

void Map::draw(sf::RenderWindow& window)
{
    background_.draw(window);
}

MaybeLocation Map::requestBuildLocation(const sf::Vector2i& point) 
{
    return tiles_.requestBuildLocation(point);
}

void Map::markOccupied(const sf::Vector2i& point)
{
    return tiles_.markOccupied(point);
}

std::vector<sf::Vector2i> Map::getPath()
{
    return mapConfig_.getPath();
}

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game