#include <Game/GameStates/MainMenuState.hpp>

#include "SFML/Graphics.hpp"

namespace game
{
namespace gamestates
{

MainMenuState::MainMenuState(sf::RenderWindow& window)
    : window_(window)
{
}

void MainMenuState::handleEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        //  TODO: refactor this into switcho-case
        if (event.type == sf::Event::Closed)
        {
            window_.close();
        }

        if (event.type == sf::Event::Resized)
        {
            // TODO: add resize support
        }

        if (event.type == sf::Event::KeyReleased)
        {
            handleKeyPressed(event);
        }
    }
}

void MainMenuState::update()
{
    return;
}

void MainMenuState::draw()
{
    menu_.draw(window_);
}

void MainMenuState::handleKeyPressed(const sf::Event event)
{
    if (event.type != sf::Event::KeyReleased)
    {
        return;
    }

    switch (event.key.code)
    {
        case sf::Keyboard::Up:
            menu_.moveUp();
            break;
        case sf::Keyboard::Down:
            menu_.moveDown();
            break;
        case sf::Keyboard::Escape:
            break;
        default:
            break;
    }

}

}  // namespace gamestates
}  // namespace game