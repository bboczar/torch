#include <Game/GameStates/GamePlay/Wave/Mob.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace wave
{

Mob::Mob(
    const MobId id,
    const WaveId waveId,
    const unsigned hp,
    const unsigned speed,
    const std::queue<sf::Vector2i>& path,
    const sf::Texture& texture)
    : id_(id)
    , waveId_(waveId)
    , status_(MobStatus::Alive)
    , heathPoints_(hp)
    , speed_(speed)
    , path_(path)
{
    position_ = path_.front();
    path_.pop();

    sprite_.setTexture(texture);
    sprite_.setPosition(position_.x, position_.y);
}

void Mob::draw(sf::RenderWindow& window)
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

void Mob::update(const float deltaTimeSec)
{
    if (!alive())
    {
        return;
    }

    move(deltaTimeSec);

    if (path_.empty())
    {
        destinationReached();
    }
}

sf::Vector2i Mob::position() const
{
    return position_;
}

void Mob::hit(const unsigned damage)
{
    if (!alive())
    {
        return;
    }

    if (damage < heathPoints_)
    {
        heathPoints_ -= damage;
        return;
    }

    die();
}

MobId Mob::id() const
{
    return id_;
}

WaveId Mob::waveId() const
{
    return waveId_;
}

MobStatus Mob::status() const
{
    return status_;
}

bool Mob::alive() const
{
    return status_ == MobStatus::Alive;
}

void Mob::move(const float deltaTimeSec)
{
    const unsigned distance = speed_ * deltaTimeSec;
    const auto destination = path_.front();

    if (position_.x == destination.x)
    {
        position_.y = calcNewPosition(position_.y, destination.y, distance);
    }
    else if (position_.y == destination.y)
    {
        position_.x = calcNewPosition(position_.x, destination.x, distance);
    }

    if (position_ == path_.front())
    {
        path_.pop();
    }
}

unsigned Mob::calcNewPosition(const unsigned current, const unsigned destination, const unsigned distance) const
{
    bool closeEnoughToWaypoint = abs(destination - current) < distance;
    if (closeEnoughToWaypoint)
    {
        return destination;
    }

    return destination > current
        ? current + distance
        : current - distance; 
}

void Mob::die()
{
    status_ = MobStatus::Killed;
}

void Mob::destinationReached()
{
    status_ = MobStatus::Destination;
}

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game