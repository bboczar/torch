#pragma once

namespace game
{

class GameState 
{

public:
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

};

}  // namespace game