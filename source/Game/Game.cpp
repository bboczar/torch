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
        auto& currentState = gameStates_.top();
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();

            currentState->handleEvent(event);
        }

        currentState->update();
        currentState->draw();
    }

    return 0;
}

void Game::setupWindow()
{
    window_.create(sf::VideoMode(800, 600), "Torch");
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(60);
}

}  // namespace game