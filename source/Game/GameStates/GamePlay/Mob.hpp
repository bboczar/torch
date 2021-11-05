#pragma once

#include <stack>

#include <SFML/Graphics.hpp>

#include <Game/Traits/DrawingObject.hpp>
#include <Game/Traits/Updatable.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class Mob : public traits::DrawingObject, traits::Updatable
{
public:
    Mob();

    virtual void draw(sf::RenderWindow& window) final;
    virtual void update(const float deltaTimeSec) final;

    sf::Vector2f position() const;
    void hit(const unsigned damage);
    bool alive() const;

private:
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