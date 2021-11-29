#include <Game/GameStates/GamePlay/GamePlay.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{

GamePlay::GamePlay(const sf::Font font)
    : font_(font)
    , gameOver_(false)
    , lives_(30)
    , cash_(60)
    , waveCooldown_(sf::seconds(20))
    , waveIdCounter_(0)
{
    assert(towerTexture_.loadFromFile("resources/tower.png") && "Missing tower texture");
    assert(mobTexture_.loadFromFile("resources/spider.png") && "Missing mob texture");
    assert(projectileTexture_.loadFromFile("resources/projectile.png") && "Missing projectile texture");
    assert(backgroundTexture_.loadFromFile("resources/map.png") && "Missing background texture");

    spawnCountdownText_.setFont(font_);
    spawnCountdownText_.setCharacterSize(18);

    cashText_.setFont(font_);
    cashText_.setCharacterSize(18);

    livesText_.setFont(font_);
    livesText_.setCharacterSize(18);

    gameOverText_.setFont(font_);
    gameOverText_.setFillColor(sf::Color::Red);
    gameOverText_.setString(std::string("GAME OVER!")); 
    gameOverText_.setCharacterSize(100);

    background_.setTexture(backgroundTexture_);
    waveSpawnClock_.restart();
}

void GamePlay::draw(sf::RenderWindow& window)
{
    background_.draw(window);
    drawText(window);

    if (gameOver_)
    {
        drawGameOver(window);
        return;
    }

    for (auto& [id, wave] : waves_)
    {
        wave.draw(window);
    }

    for (auto& tower : towers_)
    {
        tower.draw(window);
    }
}

void GamePlay::update(const float deltaTimeSec)
{
    if (gameOver_)
    {
        return;
    }

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

    updateText();
    handleClearedWaves();
}

void GamePlay::requestTower(const sf::Vector2i& position)
{
    if (cash_ < 20)
    {
        return;
    }

    towers_.emplace_back(position, towerTexture_,
        std::bind(&GamePlay::requestProjectile, this, std::placeholders::_1, std::placeholders::_2));
    cash_ -= 20;
}

void GamePlay::drawText(sf::RenderWindow& window)
{
    const auto windowSizeX = window.mapPixelToCoords(sf::Vector2i(window.getSize().x, 0)).x;

    cashText_.setPosition((windowSizeX - 100) / 3,  0);
    window.draw(cashText_);

    livesText_.setPosition(2 * (windowSizeX - 100) / 3,  0);
    window.draw(livesText_);

    spawnCountdownText_.setPosition(windowSizeX - 100,  0);
    window.draw(spawnCountdownText_);
}

void GamePlay::drawGameOver(sf::RenderWindow& window)
{
    gameOverText_.setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 50);
    window.draw(gameOverText_);
}

void GamePlay::requestProjectile(wave::Mob& target, const sf::Vector2i& position)
{
    const auto& waveIt = waves_.find(target.waveId());
    if (waveIt != waves_.end())
    {
        waveIt->second.requestProjectile(target, position);
    }
}

void GamePlay::spawnWave()
{
    const auto waveData = waveConfig_.getNextWaveData();
    waves_.emplace(
        waveIdCounter_,
        wave::Wave(
            waveIdCounter_,
            mapConfig_.getPath(),
            waveData,
            mobTexture_,
            projectileTexture_,
            std::bind(&GamePlay::handleDeadMob, this, std::placeholders::_1)));
    waveIdCounter_++;
    waveSpawnClock_.restart();
}

bool GamePlay::timeToSpawnWave() const
{
    const auto& elapsedTimeSec = waveSpawnClock_.getElapsedTime();
    return elapsedTimeSec >= waveCooldown_;
}

void GamePlay::updateText()
{
    cashText_.setString(std::string("Cash: ") + std::to_string(cash_));  

    livesText_.setString(std::string("Lives: ") + std::to_string(lives_));  

    const unsigned counter = (waveCooldown_ - waveSpawnClock_.getElapsedTime()).asSeconds();
    spawnCountdownText_.setString(std::string("Next wave: ") + std::to_string(counter));   
}

void GamePlay::handleClearedWaves()
{
    std::erase_if(waves_, [](const auto& el){ return el.second.cleared(); });
}

void GamePlay::handleDeadMob(const wave::MobStatus mobStatus)
{
    switch (mobStatus)
    {
        case wave::MobStatus::Destination:
            gameOver_ = --lives_ <= 0;
            return;  
        case wave::MobStatus::Killed:
            cash_ += 5;
            return;
        case wave::MobStatus::Alive:
            // Shall not happen
            return;
    }
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game