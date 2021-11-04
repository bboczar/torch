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

    for (auto& mob : mobs_)
    {
        mob.draw(window);
    }
}

void Map::update()
{
    if (mobs_.empty())
    {
        mobs_.emplace_back();
    }

    for (auto& mob : mobs_)
    {
        mob.update();
    }
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game