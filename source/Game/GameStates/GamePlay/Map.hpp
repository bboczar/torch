#pragma once

#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Background.hpp>
#include <Game/GameStates/GamePlay/MapConfig.hpp>
#include <Game/GameStates/GamePlay/Tower.hpp>
#include <Game/GameStates/GamePlay/Wave/Wave.hpp>
#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class Map : public traits::DrawingObject
{
public:
    Map();

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);
    void requestTower(const int x, const int y);

private:
    void requestProjectile(wave::Mob& target, const sf::Vector2i& position);
    void handleClearedWaves();

    std::unordered_map<wave::Id, wave::Wave> waves_;
    std::vector<Tower> towers_;
    Backgorund background_;

    sf::Texture towerTexture_;
    sf::Texture mobTexture_;
    sf::Texture projectileTexture_;
    sf::Texture backgroundTexture_;

    MapConfig mapConfig_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game