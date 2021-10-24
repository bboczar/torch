#pragma once

#include <memory>
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
    std::stack<std::unique_ptr<GameState>> gameStates_;
};

}  // namespace game