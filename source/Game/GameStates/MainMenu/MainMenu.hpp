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
    MainMenu(sf::Font font);

    virtual void draw(sf::RenderWindow& window) final;

    void moveUp();
    void moveDown();

private:

    enum MenuElement
    {
        MenuElement_Start,
        MenuElement_Options,
        MenuElement_Exit,
        MenuElement_Count
    };

    void placeAccordingToSize(const float width, const float height);

    MenuElement activeEntry_{MenuElement_Start};
    sf::Font font_;
    sf::Text menuElements_[MenuElement_Count];
};

}  // namespace mainmenu
}  // namespace gamestates
}  // namespace game