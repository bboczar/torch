#pragma once

#include <SFML/Graphics.hpp>

#include <Game/Traits/DrawingObject.hpp>
#include <Game/Traits/Updatable.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class Tower : public traits::DrawingObject, traits::Updatable
{
public:
    Tower();

    virtual void draw(sf::RenderWindow& window) final;
    virtual void update(const float deltaTimeSec) final;

private:
    unsigned range_;
    float fireRate_;
    sf::Vector2f position_;

    sf::Sprite sprite_;
    sf::Texture texture_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game