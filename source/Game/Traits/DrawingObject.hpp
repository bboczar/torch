#pragma once

#include "SFML/Graphics.hpp"

namespace game
{
namespace traits
{

class DrawingObject
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
};

}  // namespace traits
}  // namespace game