#include <Game/GameStates/GamePlay/Projectile.hpp>

#include <ranges>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Projectile::Projectile(
    Mob& target,
    const sf::Vector2i& position,
    const sf::Texture& texture)
    : target_(target)
    , status_(ProjectileStatus::SeekingTarget)
    , damage_(20)
    , speed_(300)
    , position_(position)
{
    sprite_.setTexture(texture);
    sprite_.setPosition(position_.x, position_.y);
}

void Projectile::draw(sf::RenderWindow& window)
{
    if (!alive())
    {
        return;
    }

    unsigned x = position_.x - (sprite_.getTexture()->getSize().x / 2);
    unsigned y = position_.y - (sprite_.getTexture()->getSize().y / 2);
    sprite_.setPosition(x, y);

    window.draw(sprite_);
}

void Projectile::update(const float deltaTimeSec)
{
    if (!alive())
    {
        return;
    }

    if (status_ == ProjectileStatus::SeekingTarget && !target_.alive())
    {
        status_ = ProjectileStatus::TargetDead;
    }
    else
    {
        lastKnownDestination_ = target_.position();
    }

    if (status_ == ProjectileStatus::SeekingTarget && closeEnoughToDestination())
    {
        targetReached();
    }
    else if (status_ == ProjectileStatus::TargetDead && closeEnoughToDestination())
    {
        destinationReached();
    }

    move(deltaTimeSec);
}

ProjectileStatus Projectile::status() const
{
    return status_;
}

bool Projectile::alive() const
{
    return status_ != ProjectileStatus::Retired;
}

void Projectile::move(const float deltaTimeSec)
{
    position_ = calcNewPosition(0,0,0);
}

sf::Vector2i Projectile::calcNewPosition(const unsigned current, const unsigned destination, const unsigned distance) const
{
    return {};
}

bool Projectile::closeEnoughToDestination() const
{
    return abs(lastKnownDestination_.x - position_.x) < 10
        && abs(lastKnownDestination_.y - position_.y) < 10;
}

void Projectile::targetReached()
{
    target_.hit(damage_);
    status_ = ProjectileStatus::Retired;
}

void Projectile::destinationReached()
{
    status_ = ProjectileStatus::Retired;
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game