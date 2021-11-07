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

    for (auto& tower : towers_)
    {
        tower.draw(window);
    }
}

void Map::update(const float deltaTimeSec)
{
    if (mobs_.empty())
    {
        mobs_.emplace_back();
        towers_.emplace_back();
    }

    for (auto& mob : mobs_)
    {
        mob.update(deltaTimeSec);
    }

    for (auto& tower : towers_)
    {
        tower.update(deltaTimeSec);
    }
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game