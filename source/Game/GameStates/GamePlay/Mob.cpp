#include <Game/GameStates/GamePlay/Mob.hpp>

#include <ranges>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Mob::Mob(
    const std::vector<sf::Vector2i>& path,
    const sf::Texture& texture)
    : status_(MobStatus::Alive)
    , heathPoints_(100)
    , speed_(150)
    // , position_({0, 210})
    // , path_({{0,330}, {195,330}, {195,540}, {324,540}, {324,230}, {535,230}, {535,540}, {710,540}, {710,90}, {190,90}, {190,210}})  // TODO: unhardcode
{
    for (const auto& point : path | std::views::reverse)
    {
        path_.push(point);
    }

    position_ = path_.top();
    path_.pop();

    sprite_.setTexture(texture);
    sprite_.setPosition(position_.x, position_.y);
}

void Mob::draw(sf::RenderWindow& window)
{
    unsigned x = position_.x - (sprite_.getTexture()->getSize().x / 2);
    unsigned y = position_.y - (sprite_.getTexture()->getSize().y / 2);
    sprite_.setPosition(x, y);

    window.draw(sprite_);
}

void Mob::update(const float deltaTimeSec)
{
    if (status_ != MobStatus::Alive)
    {
        return;
    }

    move(deltaTimeSec);
}

sf::Vector2i Mob::position() const
{
    return position_;
}

void Mob::hit(const unsigned damage)
{
    if (damage < heathPoints_)
    {
        heathPoints_ -= damage;
        return;
    }

    die();
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
    const float distance = speed_ * deltaTimeSec;
    const auto destination = path_.top();

    if (position_.x == destination.x)
    {
        position_.y = calcNewPosition(position_.y, destination.y, distance);
    }
    else if (position_.y == destination.y)
    {
        position_.x = calcNewPosition(position_.x, destination.x, distance);
    }

    if (path_.empty())
    {
        destinationReached();
    }
}

float Mob::calcNewPosition(const float current, const float destination, const float distance)
{
    bool closeEnoughToWaypoint = abs(destination - current) < distance;
    if (closeEnoughToWaypoint)
    {
        path_.pop();
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

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game