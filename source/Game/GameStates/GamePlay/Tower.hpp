#pragma once

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Wave/Mob.hpp>
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
    Tower(const int x, const int y, const sf::Texture& texture,
        std::function<void(Mob&, const sf::Vector2i&)> projectileRequest);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec, std::vector<Mob>& mobs);

private:
    bool inRange(const Mob& mob) const;
    bool canFire() const;

    unsigned range_;
    sf::Time cooldown_;
    sf::Vector2i position_;

    std::function<void(Mob&, const sf::Vector2i&)> projectileRequest_;

    sf::Clock clock_;

    sf::Sprite sprite_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game