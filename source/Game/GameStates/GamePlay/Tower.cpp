#include <Game/GameStates/GamePlay/Tower.hpp>

#include <iostream>

#include <cassert>
#include <cmath>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Tower::Tower()
    : range_(350)
    , cooldown_(sf::seconds(1.0))
    , position_({240, 260})
{
    if (!texture_.loadFromFile("resources/tower.png"))
    {
        assert(false && "Missing tower texture");
    }

    clock_.restart();

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

void Tower::update(const float deltaTimeSec, const std::vector<Mob>& mobs)
{
    if (!canFire())
    {
        return;
    }

    const auto& targetIter = std::find_if(
        mobs.begin(), mobs.end(), [this](const auto& mob){ return inRange(mob); });

    if (targetIter == mobs.end())
    {
        return;
    }
    
    std::cout << "FIRE!" << std::endl;
    clock_.restart();
    // fireCallback(*targetIter);
}

bool Tower::inRange(const Mob& mob) const
{
    const auto& mobPosition = mob.position();
    const auto& distance = sqrt(
        pow(mobPosition.x - position_.x, 2.0) + pow(mobPosition.y - position_.y, 2.0));
    return range_ >= distance;
}

bool Tower::canFire() const
{
    const auto& elapsedTimeSec = clock_.getElapsedTime();
    return elapsedTimeSec >= cooldown_;
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game