#include <Game/GameStates/GamePlay/Mob.hpp>

#include <iostream>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Mob::Mob()
    : speed_(50)
    , position_({0, 210})
    , path_({{190,90}, {190,210}})  // TODO: unhardcode
{
    texture_.loadFromFile("resources/spider.png");
    sprite_.setTexture(texture_);
    sprite_.setPosition(position_);
}

void Mob::draw(sf::RenderWindow& window)
{
    window.draw(sprite_);
}

void Mob::update(const float deltaTimeSec)
{
    if (!alive())
    {
        // This should not happen?
        return;
    }

    move(deltaTimeSec);

    unsigned x = position_.x - (texture_.getSize().x / 2);
    unsigned y = position_.y - (texture_.getSize().y / 2);
    sprite_.setPosition(x, y);
}

sf::Vector2f Mob::position() const
{
    return position_;
}

void Mob::hit(const unsigned damage)
{
    return;
}

bool Mob::alive() const
{
    return heathPoints_ > 0;
}

void Mob::move(const float deltaTimeSec)
{
    if (path_.empty())
    {
        // TODO: Mod should die and life should be lost
        return;
    }

    const float distance = speed_ * deltaTimeSec;
    const auto destination = path_.top();

    if (position_.x == destination.x)
    {
        position_.y = calcNewPosition(position_.y, destination.y, distance);
        return;
    }

    if (position_.y == destination.y)
    {
        position_.x = calcNewPosition(position_.x, destination.x, distance);
        return;
    }

    // TODO: Handle this but should not happen
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

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game