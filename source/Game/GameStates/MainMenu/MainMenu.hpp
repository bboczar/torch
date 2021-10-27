#pragma once

#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace mainmenu
{

class MainMenu : public traits::DrawingObject
{
public:
    virtual void draw(sf::RenderWindow& window) final;
};

}  // namespace mainmenu
}  // namespace gamestates
}  // namespace game