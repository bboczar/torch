#include <Game/GameStates/GamePlay/Background.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Backgorund::Backgorund()
{}

void Backgorund::setTexture(const sf::Texture& texture)
{
    background_.setTexture(texture);
}

void Backgorund::draw(sf::RenderWindow& window)
{
    window.draw(background_);
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game