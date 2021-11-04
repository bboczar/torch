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
    map_.draw(window);
}

void GamePlay::update()
{
    map_.update();
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game