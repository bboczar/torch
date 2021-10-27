#include <Game/Game.hpp>

#include <Game/GameStates/MainMenuState.hpp>

namespace game
{

Game::Game()
{
    setupWindow();
    gameStates_.push(std::make_unique<gamestates::MainMenuState>());
}

int Game::loop()
{
    while (window_.isOpen())
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

            if (event.type == sf::Event::KeyPressed)
            {
                handleKeyPressed(event);
            }
        }

        auto& currentState = gameStates_.top();
        if (!currentState->handleEvent(event))
        {
            gameStates_.pop();
            continue;
        }
        
        currentState->update();

        window_.clear(sf::Color::Black);
        currentState->draw(window_);
        window_.display();
    }

    return 0;
}

void Game::setupWindow()
{
    window_.create(sf::VideoMode(800, 600), "Torch");
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(60);
}

void Game::handleKeyPressed(const sf::Event keyPressedEvent)
{
    return;
}

}  // namespace game