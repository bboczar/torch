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

class Mob : public traits::DrawingObject
{
public:
    Mob();

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);

    sf::Vector2f position() const;
    void hit(const unsigned damage);
    bool alive() const;

private:
    void move(const float deltaTimeSec);
    float calcNewPosition(const float current, const float destination, const float distance);
    void die();

    unsigned heathPoints_;
    float speed_;
    sf::Vector2f position_;
    std::stack<sf::Vector2f> path_;

    sf::Sprite sprite_;
    sf::Texture texture_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game