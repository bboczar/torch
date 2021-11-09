#include <Game/GameStates/GamePlay/Mob.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Mob::Mob(const sf::Texture& texture)
    : heathPoints_(100)
    , speed_(150)
    , position_({0, 210})
    , path_({{0,330}, {195,330}, {195,540}, {324,540}, {324,230}, {535,230}, {535,540}, {710,540}, {710,90}, {190,90}, {190,210}})  // TODO: unhardcode
{
    sprite_.setTexture(texture);
    sprite_.setPosition(position_);
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
    if (!alive())
    {
        // This should not happen?
        return;
    }

    move(deltaTimeSec);
}

sf::Vector2f Mob::position() const
{
    return position_;
}

void Mob::hit(const unsigned damage)
{
    if (damage > heathPoints_)
    {
        heathPoints_ -= damage;
        return;
    }

    die();
}

// TODO: Distinguish killed vs reached destination
bool Mob::alive() const
{
    return heathPoints_ > 0;
}

void Mob::move(const float deltaTimeSec)
{
    if (path_.empty())
    {
        // TODO: Life should be lost
        die();
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

// TODO: implement
void Mob::die()
{
    return;
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game