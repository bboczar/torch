#pragma once

#include <memory>
#include <stack>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Game/GameState.hpp>

namespace game
{

class Game
{
public:
    Game();
    int loop();

private:
    void setupWindow();
    void setupResources();
    void updateFps(const float deltaTimeSec);
    void draw();

    float elapsedTime();

    void dropState();
    void pushState(const GameStateType stateType);
    bool hasState() const;
    std::unique_ptr<GameState>& currentState();

    sf::RenderWindow window_;
    sf::Font font_;
    sf::Clock clock_;
    sf::Text fpsText_;

    std::stack<std::unique_ptr<GameState>> gameStates_;
};

}  // namespace game