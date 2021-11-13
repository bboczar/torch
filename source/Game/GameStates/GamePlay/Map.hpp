#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Background.hpp>
#include <Game/GameStates/GamePlay/MapConfig.hpp>
#include <Game/GameStates/GamePlay/Mob.hpp>
#include <Game/GameStates/GamePlay/Projectile.hpp>
#include <Game/GameStates/GamePlay/Tower.hpp>
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
    void requestProjectile(Mob& target, const sf::Vector2i& position);
    void dropDeadMobs();

    std::vector<Mob> mobs_;
    std::vector<Tower> towers_;
    std::vector<Projectile> projectiles_;
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