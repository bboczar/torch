#include <Game/GameStates/GamePlay/Background.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{

Backgorund::Backgorund()
{
    if (!backgroundTexture_.loadFromFile("resources/map.png"))
    {
        assert(false && "Missing background texture");
    }
    background_.setTexture(backgroundTexture_);
}

void Backgorund::draw(sf::RenderWindow& window)
{
    window.draw(background_);
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game