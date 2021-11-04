#include <Game/Game.hpp>

#include <Game/GameStates/GamePlayState.hpp>
#include <Game/GameStates/MainMenuState.hpp>

namespace game
{

Game::Game()
{
    setupWindow();
    setupResources();
    pushState(GameStateType::MainMenu);
}

int Game::loop()
{
    while (window_.isOpen() and hasState())
    {
        updateFps();

        auto& state = currentState();
        const auto desiredState = state->handleEvents();
        {
            if (!desiredState)
            {
                dropState();
                continue;
            }

            if (desiredState != state->type())
            {
                pushState(desiredState.value());
                continue;
            }
        }
        
        // TODO: implement delta time in update
        state->update();
        state->draw();

        draw();
    }

    return 0;
}

void Game::setupWindow()
{
    window_.create(sf::VideoMode(800, 600), "Torch");
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(60);
}

void Game::setupResources()
{
    font_.loadFromFile("resources/Bebas-Regular.ttf");
    fpsText_.setFont(font_);
    fpsText_.setCharacterSize(16);
}

void Game::updateFps()
{
    float fps =  1/(clock_.restart().asSeconds());
    fpsText_.setString(std::to_string(fps));   
}

void Game::draw()
{
    window_.draw(fpsText_);
    window_.display();
}

void Game::dropState()
{
    gameStates_.pop();
}

void Game::pushState(const GameStateType stateType)
{
    switch (stateType)
    {
        case GameStateType::MainMenu:
            gameStates_.push(std::make_unique<gamestates::MainMenuState>(window_, font_));
            break;
        case GameStateType::GamePlay:
            gameStates_.push(std::make_unique<gamestates::GamePlayState>(window_, font_));
            break;   
        // TODO: Add other states 
        default:
            break;
    }
}

bool Game::hasState() const
{
    return not gameStates_.empty();
}

std::unique_ptr<GameState>& Game::currentState()
{
    return gameStates_.top();
}

}  // namespace game