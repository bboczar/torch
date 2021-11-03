#include <Game/GameStates/GamePlay/GamePlay.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

GamePlay::GamePlay()
{
}

void GamePlay::draw(sf::RenderWindow& window)
{
    background_.draw(window);
}

void GamePlay::update()
{
    return;
}


}  // namespace gameplay
}  // namespace gamestates
}  // namespace game