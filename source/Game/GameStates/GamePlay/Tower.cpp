#include <Game/GameStates/GamePlay/Tower.hpp>

#include <cmath>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Tower::Tower(const int x, const int y, const sf::Texture& texture,
    std::function<void(wave::Mob&, const sf::Vector2i&)> projectileRequest)
    : range_(500)
    , cooldown_(sf::seconds(1.0))
    , position_({x, y})
    , projectileRequest_(projectileRequest)
{
    clock_.restart();

    sprite_.setTexture(texture);
    sprite_.setPosition(float(x), float(y));
}

void Tower::draw(sf::RenderWindow& window)
{
    unsigned x = position_.x - (sprite_.getTexture()->getSize().x / 2);
    unsigned y = position_.y - (sprite_.getTexture()->getSize().y / 2);
    sprite_.setPosition(float(x), float(y));

    window.draw(sprite_);
}

void Tower::update(const float deltaTimeSec, std::vector<wave::Mob>& mobs)
{
    if (!canFire())
    {
        return;
    }

    const auto& targetIter = std::find_if(
        mobs.begin(), mobs.end(), [this](const auto& mob){ return mob.alive() and inRange(mob); });

    if (targetIter == mobs.end())
    {
        return;
    }
    
    clock_.restart();
    projectileRequest_(*targetIter, position_);
}

bool Tower::inRange(const wave::Mob& mob) const
{
    const auto& mobPosition = mob.position();
    const auto& distance = sqrt(
        pow(mobPosition.x - position_.x, 2) + pow(mobPosition.y - position_.y, 2));
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