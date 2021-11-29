#pragma once

#include <SFML/Graphics.hpp>

#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

class Backgorund : public traits::DrawingObject
{
public:
    Backgorund();

    virtual void draw(sf::RenderWindow& window) final;
    void setTexture(const sf::Texture& texture);

private:
    sf::Sprite background_;
};

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game