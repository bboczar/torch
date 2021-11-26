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
    virtual ~GameState() {};
    virtual DesiredState handleEvents() = 0;
    virtual void update(const float) = 0;
    virtual void draw() = 0;
    virtual GameStateType type() const = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
};

}  // namespace game