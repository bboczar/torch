#pragma once

#include <stack>

#include <SFML/Graphics.hpp>

#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

enum class MobStatus
{
    Alive,
    Killed,
    Destination
};

class Mob : public traits::DrawingObject
{
public:
    Mob(const std::vector<sf::Vector2i>& path, const sf::Texture& texture);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);
    void hit(const unsigned damage);

    sf::Vector2i position() const;
    MobStatus status() const;
    bool alive() const;

private:
    void move(const float deltaTimeSec);
    unsigned calcNewPosition(const unsigned current, const unsigned destination, const unsigned distance) const;

    void die();
    void destinationReached();

    MobStatus status_;
    unsigned heathPoints_;
    unsigned speed_;
    sf::Vector2i position_;
    std::stack<sf::Vector2i> path_;

    sf::Sprite sprite_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game