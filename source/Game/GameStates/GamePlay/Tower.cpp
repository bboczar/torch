#include <Game/GameStates/GamePlay/Tower.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Tower::Tower()
    : range_(150)
    , fireRate_(0.5)
    , position_({240, 260})
{
    if (!texture_.loadFromFile("resources/tower.png"))
    {
        assert(false && "Missing tower texture");
    }

    sprite_.setTexture(texture_);
    sprite_.setPosition(position_);
}

void Tower::draw(sf::RenderWindow& window)
{
    unsigned x = position_.x - (texture_.getSize().x / 2);
    unsigned y = position_.y - (texture_.getSize().y / 2);
    sprite_.setPosition(x, y);

    window.draw(sprite_);
}

void Tower::update(const float deltaTimeSec)
{
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game