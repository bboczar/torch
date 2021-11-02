#pragma once

#include <SFML/Graphics.hpp>

#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class Backgorund : public traits::DrawingObject
{
public:
    Backgorund();

    virtual void draw(sf::RenderWindow& window) final;

private:
    sf::Sprite background_;
    sf::Texture backgroundTexture_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game