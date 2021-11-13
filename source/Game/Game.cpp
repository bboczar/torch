#include <Game/Game.hpp>

#include <cassert>

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
        const float deltaTimeSec = elapsedTime();

        updateFps(deltaTimeSec);

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
        
        state->update(deltaTimeSec);
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

void Game::updateFps(const float deltaTimeSec)
{
    const float fps =  1/(deltaTimeSec);
    fpsText_.setString(std::to_string(fps));   
}

void Game::draw()
{
    window_.draw(fpsText_);
    window_.display();
}

float Game::elapsedTime()
{
    return clock_.restart().asSeconds();
}

void Game::dropState()
{
    gameStates_.pop();
    if (not gameStates_.empty())
    {
        gameStates_.top()->resume();
    }
}

void Game::pushState(const GameStateType stateType)
{
    if (not gameStates_.empty())
    {
        gameStates_.top()->pause();
    }

    switch (stateType)
    {
        case GameStateType::MainMenu:
            gameStates_.push(std::make_unique<gamestates::MainMenuState>(window_, font_));
            break;
        case GameStateType::GamePlay:
            gameStates_.push(std::make_unique<gamestates::GamePlayState>(window_, font_));
            break;   
        default:
            assert(false and "Unknown game state");
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