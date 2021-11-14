#pragma once

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Wave/Mob.hpp>
#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace wave
{

enum class ProjectileStatus
{
    SeekingTarget,
    TargetDead,
    Retired
};

class Projectile : public traits::DrawingObject
{
public:
    Projectile(
        const MobId targetId,
        const sf::Vector2i& position,
        const sf::Texture& texture,
        std::function<Mob&(const MobId)> getTarget);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);

    ProjectileStatus status() const;
    bool alive() const;

private:
    void move(const float deltaTimeSec);
    void setNewPosition(const unsigned distance);
    bool closeEnoughToDestination() const;

    void targetReached(Mob& target);
    void destinationReached();

    MobId targetId_;
    sf::Vector2i lastKnownDestination_;

    ProjectileStatus status_;
    unsigned damage_;
    unsigned speed_;
    sf::Vector2i position_;

    std::function<Mob&(const MobId)> getTarget_;

    sf::Sprite sprite_;
};

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game