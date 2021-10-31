#pragma once

#include <optional>

namespace game
{

enum class GameStateType
{
    MainMenu,
    Options,
    GamePlay,
    PauseMenu
};

class GameState 
{

public:
    virtual std::optional<GameStateType> handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

};

}  // namespace game