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
    if (towers_.empty())  // TODO: remove, temporary for testing
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
        tower.update(deltaTimeSec, mobs_);
    }

    dropDeadMobs();
}

void Map::dropDeadMobs()
{
    mobs_.erase(
        std::remove_if(mobs_.begin(), mobs_.end(), [](const Mob& m){ return !m.alive(); }),
        mobs_.end()
    );
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game