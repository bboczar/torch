#include <Game/GameStates/GamePlay/GamePlay.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

GamePlay::GamePlay(
    const sf::Font font)
    : map_(font)
{
}

void GamePlay::draw(sf::RenderWindow& window)
{
    map_.draw(window);
}

void GamePlay::update(const float deltaTimeSec)
{
    map_.update(deltaTimeSec);
}

void GamePlay::requestTower(const int x, const int y)
{
    map_.requestTower({x, y});
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game