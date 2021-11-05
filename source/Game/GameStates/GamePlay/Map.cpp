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

void Map::update(const float deltaTimeSec)
{
    if (mobs_.empty())
    {
        mobs_.emplace_back();
    }

    for (auto& mob : mobs_)
    {
        mob.update(deltaTimeSec);
    }
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game