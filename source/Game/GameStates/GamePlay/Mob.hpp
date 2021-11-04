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

class Mob : public traits::DrawingObject, traits::Updatable
{
public:
    Mob();

    virtual void draw(sf::RenderWindow& window) final;
    virtual void update() final;

    sf::Vector2f position() const;
    void hit(const unsigned damage);

private:
    unsigned heathPoints_;
    float speed_;
    sf::Vector2f position_;
    std::vector<sf::Vector2f> path_;

    sf::Sprite sprite_;
    sf::Texture texture_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game