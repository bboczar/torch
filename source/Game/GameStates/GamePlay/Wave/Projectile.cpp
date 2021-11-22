#include <Game/GameStates/GamePlay/Wave/Projectile.hpp>

#include <cmath>
#include <ranges>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace wave
{

Projectile::Projectile(
    const MobId targetId,
    const sf::Vector2i& position,
    const sf::Texture& texture,
    std::function<MaybeMobRef(const MobId)> getTarget)
    : targetId_(targetId)
    , status_(ProjectileStatus::SeekingTarget)
    , damage_(10)
    , speed_(700)
    , position_(position)
    , getTarget_(getTarget)
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

    MaybeMobRef target = getTarget_(targetId_);
    if (target and target->get().alive())
    {
        lastKnownDestination_ = target->get().position();
    }
    else
    {
        status_ = ProjectileStatus::TargetDead;
    }

    if (status_ == ProjectileStatus::SeekingTarget && closeEnoughToDestination())
    {
        targetReached(target->get());
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
    if (lastKnownDestination_.x == position_.x)
    {
        position_.y += distance * (lastKnownDestination_.y > position_.y ? 1 : -1);
        return;
    }

    if (lastKnownDestination_.y == position_.y)
    {
        position_.x += distance * (lastKnownDestination_.x > position_.x ? 1 : -1);
        return;
    }

    const float tanAlpha =
        float(lastKnownDestination_.y - position_.y) / float(lastKnownDestination_.x - position_.x);
    const float alpha = atan(tanAlpha);

    position_.x += abs(distance * cos(alpha)) * (lastKnownDestination_.x > position_.x ? 1 : -1);
    position_.y += abs(distance * sin(alpha)) * (lastKnownDestination_.y > position_.y ? 1 : -1);
}

bool Projectile::closeEnoughToDestination() const
{
    return abs(lastKnownDestination_.x - position_.x) < 20
        && abs(lastKnownDestination_.y - position_.y) < 20;
}

void Projectile::targetReached(Mob& target)
{
    target.hit(damage_);
    status_ = ProjectileStatus::Retired;
}

void Projectile::destinationReached()
{
    status_ = ProjectileStatus::Retired;
}

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game