#include <Game/GameStates/GamePlay/Background.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Backgorund::Backgorund()
{
    backgroundTexture_.loadFromFile("resources/map.png");
    background_.setTexture(backgroundTexture_);
}

void Backgorund::draw(sf::RenderWindow& window)
{
    window.draw(background_);
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game