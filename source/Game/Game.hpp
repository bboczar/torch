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
    sf::RenderWindow window_;
    std::stack<std::unique_ptr<GameState>> gameStates_;
};

}  // namespace game