#include <Game/GameStates/GamePlay/Projectile.hpp>

#include <cmath>
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
    , speed_(700)
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
        return;
    }
    else if (status_ == ProjectileStatus::TargetDead && closeEnoughToDestination())
    {
        destinationReached();
        return;
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
    const unsigned distance = speed_ * deltaTimeSec;
    setNewPosition(distance);
}

void Projectile::setNewPosition(const unsigned distance)
{
    const float tanAlpha =
        (lastKnownDestination_.y - position_.y) / (lastKnownDestination_.x - position_.x);

    const float alpha = atan(tanAlpha);
    position_.x += abs(distance * cos(alpha)) * (lastKnownDestination_.x > position_.x ? 1 : -1);
    position_.y += abs(distance * sin(alpha)) * (lastKnownDestination_.y > position_.y ? 1 : -1);
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