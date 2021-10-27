#include <Game/GameStates/MainMenuState.hpp>

#include "SFML/Graphics.hpp"

namespace game
{
namespace gamestates
{

MainMenuState::MainMenuState()
{
}

bool MainMenuState::handleEvent(sf::Event)
{
    bool stillAlive = true;
    return stillAlive;
}

void MainMenuState::update()
{
    return;
}

void MainMenuState::draw(sf::RenderWindow& window)
{
    menu_.draw(window);
}


}  // namespace gamestates
}  // namespace game