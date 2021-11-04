#include <Game/GameStates/GamePlay/Mob.hpp>

#include <iostream>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Mob::Mob()
    : speed_(0.25)
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

void Mob::update()
{
    position_.x = position_.x + speed_;
    position_.y = position_.y + speed_;
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

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game