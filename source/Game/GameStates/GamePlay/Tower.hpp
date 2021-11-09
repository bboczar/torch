#pragma once

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Mob.hpp>
#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class Tower : public traits::DrawingObject
{
public:
    Tower(const int x, const int y, const sf::Texture& texture);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec, const std::vector<Mob>& mobs);

private:
    bool inRange(const Mob& mob) const;
    bool canFire() const;

    unsigned range_;
    sf::Time cooldown_;
    sf::Vector2i position_;

    sf::Clock clock_;

    sf::Sprite sprite_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game