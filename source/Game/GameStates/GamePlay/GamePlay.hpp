#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Map/Background.hpp>
#include <Game/GameStates/GamePlay/Map/MapConfig.hpp>
#include <Game/GameStates/GamePlay/Tower.hpp>
#include <Game/GameStates/GamePlay/Wave/Mob.hpp>
#include <Game/GameStates/GamePlay/Wave/Wave.hpp>
#include <Game/GameStates/GamePlay/Wave/WaveConfig.hpp>
#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class GamePlay : public traits::DrawingObject
{
public:
    GamePlay(const sf::Font font);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);
    void requestTower(const sf::Vector2i& position);

private:
    void drawText(sf::RenderWindow& window);
    void drawGameOver(sf::RenderWindow& window);
    void requestProjectile(wave::Mob& target, const sf::Vector2i& position);
    void spawnWave();
    bool timeToSpawnWave() const;
    void updateText();
    void handleClearedWaves();
    void handleDeadMob(const wave::MobStatus mobStatus);

    std::map<wave::WaveId, wave::Wave> waves_;
    std::vector<Tower> towers_;
    map::Backgorund background_;

    sf::Texture towerTexture_;
    sf::Texture mobTexture_;
    sf::Texture projectileTexture_;
    sf::Texture backgroundTexture_;

    sf::Font font_;
    sf::Text spawnCountdownText_;
    sf::Text cashText_;
    sf::Text livesText_;
    sf::Text gameOverText_;

    bool gameOver_;
    int lives_;
    unsigned cash_;

    sf::Time waveCooldown_;
    sf::Clock waveSpawnClock_;
    wave::WaveId waveIdCounter_;

    map::MapConfig mapConfig_;
    wave::WaveConfig waveConfig_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game