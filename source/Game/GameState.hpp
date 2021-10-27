#pragma once

#include <SFML/Window.hpp>

namespace game
{

class GameState 
{

public:
    virtual bool handleEvent(sf::Event) = 0;
    virtual void update() = 0;
    // TODO: make it a DrawingObject
    virtual void draw(sf::RenderWindow&) = 0;

};

}  // namespace game