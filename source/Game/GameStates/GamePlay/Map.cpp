#include <Game/GameStates/GamePlay/Map.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Map::Map()
{
    assert(towerTexture_.loadFromFile("resources/tower.png") && "Missing tower texture");
    assert(mobTexture_.loadFromFile("resources/spider.png") && "Missing mob texture");
    assert(projectileTexture_.loadFromFile("resources/projectile.png") && "Missing projectile texture");
    assert(backgroundTexture_.loadFromFile("resources/map.png") && "Missing background texture");

    background_.setTexture(backgroundTexture_);
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
    if (mobs_.empty())  // TODO: remove, temporary for testing
    {
        mobs_.emplace_back(mapConfig_.getPath(), mobTexture_);
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

void Map::requestTower(const int x, const int y)
{
   towers_.emplace_back(x, y, towerTexture_);
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