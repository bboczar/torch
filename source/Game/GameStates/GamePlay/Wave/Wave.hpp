#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/MapConfig.hpp>
#include <Game/GameStates/GamePlay/Wave/Mob.hpp>
#include <Game/GameStates/GamePlay/Wave/Projectile.hpp>
#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace wave
{

using Id = unsigned;

class Wave : public traits::DrawingObject
{
public:
    Wave(
        const Id id,
        const std::vector<sf::Vector2i>& path,
        const sf::Texture& mobTexture,
        const sf::Texture& projectileTexture);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);
    bool cleared() const;
    void requestProjectile(Mob& target, const sf::Vector2i& position);

    std::vector<Mob>& getMobs();

private:
    std::vector<Mob> mobs_;
    std::vector<Projectile> projectiles_;

    const Id id_;
    const std::vector<sf::Vector2i> path_;

    const sf::Texture& mobTexture_;
    const sf::Texture& projectileTexture_;
};

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game