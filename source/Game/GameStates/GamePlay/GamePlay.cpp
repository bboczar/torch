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

void GamePlay::requestTower(const sf::Vector2i& position)
{
    map_.requestTower(position);
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game