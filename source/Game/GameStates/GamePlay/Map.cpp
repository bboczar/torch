#include <Game/GameStates/GamePlay/Map.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Map::Map()
{
}

void Map::draw(sf::RenderWindow& window)
{
    background_.draw(window);
}

void Map::update()
{
    return;
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game