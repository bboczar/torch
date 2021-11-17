#include <Game/GameStates/GamePlay/Map.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Map::Map()
    : waveCooldown_(sf::seconds(10))
    , waveIdCounter_(0)
{
    assert(towerTexture_.loadFromFile("resources/tower.png") && "Missing tower texture");
    assert(mobTexture_.loadFromFile("resources/spider.png") && "Missing mob texture");
    assert(projectileTexture_.loadFromFile("resources/projectile.png") && "Missing projectile texture");
    assert(backgroundTexture_.loadFromFile("resources/map.png") && "Missing background texture");

    background_.setTexture(backgroundTexture_);
    clock_.restart();
}

void Map::draw(sf::RenderWindow& window)
{
    background_.draw(window);

    for (auto& [id, wave] : waves_)
    {
        wave.draw(window);
    }

    for (auto& tower : towers_)
    {
        tower.draw(window);
    }
}

void Map::update(const float deltaTimeSec)
{
    for (auto& [Id, wave] : waves_)
    {
        wave.update(deltaTimeSec);
    }

    for (auto& tower : towers_)
    {
        for (auto& [Id, wave] : waves_)
        {
            tower.update(deltaTimeSec, wave.getMobs());
        }
    }

    spawnWave();
    handleClearedWaves();
}

void Map::requestTower(const sf::Vector2i& position)
{
    towers_.emplace_back(position, towerTexture_,
        std::bind(&Map::requestProjectile, this, std::placeholders::_1, std::placeholders::_2));
}

void Map::requestProjectile(wave::Mob& target, const sf::Vector2i& position)
{
    const auto& waveIt = waves_.find(target.waveId());
    if (waveIt != waves_.end())
    {
        waveIt->second.requestProjectile(target, position);
    }
}

void Map::spawnWave()
{
    if (timeToSpawnWave())
    {
        waves_.emplace(waveIdCounter_, wave::Wave(waveIdCounter_, mapConfig_.getPath(), mobTexture_, projectileTexture_));
        waveIdCounter_++;
        clock_.restart();
    }
}

bool Map::timeToSpawnWave() const
{
    const auto& elapsedTimeSec = clock_.getElapsedTime();
    return elapsedTimeSec >= waveCooldown_;
}

void Map::handleClearedWaves()
{
    std::erase_if(waves_, [](const auto& el){ return el.second.cleared(); });
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game