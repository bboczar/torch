#pragma once

#include <stack>

#include <SFML/Window.hpp>

#include <Game/GameState.hpp>

namespace game
{

class Game
{
public:
    Game();
    int loop();
    void setupWindow();

private:
    sf::Window window_;
    std::stack<GameState> gameStates_;
};

}  // namespace game