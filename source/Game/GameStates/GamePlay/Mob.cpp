#include <Game/GameStates/GamePlay/Mob.hpp>

#include <iostream>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Mob::Mob()
    : speed_(20)
    , position_({0, 0})
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

    position_.x += deltaTimeSec * speed_;
    position_.y += deltaTimeSec * speed_;
    sprite_.setPosition(position_);
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

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game