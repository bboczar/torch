#include <Game/GameStates/GamePlay/Map/Background.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
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

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game