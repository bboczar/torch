#include <Game/GameStates/GamePlay/Map.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Map::Map(const sf::Font font)
    : font_(font)
    , waveCooldown_(sf::seconds(20))
    , waveIdCounter_(0)
{
    assert(towerTexture_.loadFromFile("resources/tower.png") && "Missing tower texture");
    assert(mobTexture_.loadFromFile("resources/spider.png") && "Missing mob texture");
    assert(projectileTexture_.loadFromFile("resources/projectile.png") && "Missing projectile texture");
    assert(backgroundTexture_.loadFromFile("resources/map.png") && "Missing background texture");

    spawnCountdownText_.setFont(font_);
    spawnCountdownText_.setCharacterSize(16);

    background_.setTexture(backgroundTexture_);
    waveSpawnClock_.restart();
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

    spawnCountdownText_.setPosition(window.getSize().x - 90,  0);
    window.draw(spawnCountdownText_);
}

void Map::update(const float deltaTimeSec)
{
    if (timeToSpawnWave() && not waveConfig_.empty())
    {
        spawnWave();
    }

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

    updateWaveCountdownText();
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
    const auto waveData = waveConfig_.getNextWaveData();
    waves_.emplace(waveIdCounter_, wave::Wave(waveIdCounter_, mapConfig_.getPath(), waveData.mobCount, mobTexture_, projectileTexture_));
    waveIdCounter_++;
    waveSpawnClock_.restart();
}

bool Map::timeToSpawnWave() const
{
    const auto& elapsedTimeSec = waveSpawnClock_.getElapsedTime();
    return elapsedTimeSec >= waveCooldown_;
}

void Map::updateWaveCountdownText()
{
    const unsigned counter = (waveCooldown_ - waveSpawnClock_.getElapsedTime()).asSeconds();
    spawnCountdownText_.setString(std::string("Next wave: ") + std::to_string(counter));   
}

void Map::handleClearedWaves()
{
    std::erase_if(waves_, [](const auto& el){ return el.second.cleared(); });
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game