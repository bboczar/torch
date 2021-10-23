#pragma once

#include <SFML/Window/Event.hpp>

namespace game
{

class GameState 
{

public:
    virtual void handleEvent(sf::Event) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

};

}  // namespace game