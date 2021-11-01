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

using DesiredState = std::optional<GameStateType>; 

class GameState 
{
public:
    virtual DesiredState handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual GameStateType type() const = 0;
};

}  // namespace game