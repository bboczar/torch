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

enum class ProjectileStatus
{
    SeekingTarget,
    TargetDead,
    Retired
};

class Projectile : public traits::DrawingObject
{
public:
    Projectile(Mob& target, const sf::Vector2i& position, const sf::Texture& texture);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);

    ProjectileStatus status() const;
    bool alive() const;

private:
    void move(const float deltaTimeSec);
    void setNewPosition(const unsigned distance);
    bool closeEnoughToDestination() const;

    void targetReached();
    void destinationReached();

    Mob& target_;
    sf::Vector2i lastKnownDestination_;

    ProjectileStatus status_;
    unsigned damage_;
    unsigned speed_;
    sf::Vector2i position_;

    sf::Sprite sprite_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game