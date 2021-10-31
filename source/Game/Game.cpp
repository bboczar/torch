#include <Game/Game.hpp>

#include <Game/GameStates/MainMenuState.hpp>

namespace game
{

Game::Game()
{
    setupWindow();
    font_.loadFromFile("resources/Bebas-Regular.ttf");
    fpsText_.setFont(font_);
    fpsText_.setCharacterSize(24);

    gameStates_.push(std::make_unique<gamestates::MainMenuState>(window_, font_));
}

int Game::loop()
{
    while (window_.isOpen())
    {
        if (gameStates_.empty())
        {
            return 0;
        }

        float fps =  1/(clock_.restart().asSeconds());
        fpsText_.setString(std::to_string(fps));

        auto& currentState = gameStates_.top();
        const auto desiredState = currentState->handleEvents();
        {
            if (!desiredState)
            {
                gameStates_.pop();
                continue;
            }

            // TODO: add support for state change
        }
           
        currentState->update();

        window_.clear(sf::Color::Black);
        currentState->draw();
        window_.draw(fpsText_);
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

}  // namespace game