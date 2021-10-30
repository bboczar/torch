#include <Game/GameStates/MainMenuState.hpp>

#include "SFML/Graphics.hpp"

namespace game
{
namespace gamestates
{

MainMenuState::MainMenuState(
    sf::RenderWindow& window,
    sf::Font font)
    : window_(window)
    , menu_(mainmenu::MainMenu(font))
{
}

void MainMenuState::handleEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::Resized:
                window_.setSize(sf::Vector2u(event.size.width, event.size.height));
                break;
            case sf::Event::KeyReleased:
                handleKeyPressed(event);
                break;
            default:
                // No need to handle other events
                break;
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