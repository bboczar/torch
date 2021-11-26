#include <Game/GameStates/MainMenu/MainMenu.hpp>

namespace game
{
namespace gamestates
{
namespace mainmenu
{

MainMenu::MainMenu(const sf::Font font)
    : font_(font)
{
    menuElements_[MenuElement_Start].setFont(font_);
    menuElements_[MenuElement_Start].setFillColor(sf::Color::Red);
    menuElements_[MenuElement_Start].setString("Play");

    menuElements_[MenuElement_Options].setFont(font_);
    menuElements_[MenuElement_Options].setFillColor(sf::Color::White);
    menuElements_[MenuElement_Options].setString("Options");

    menuElements_[MenuElement_Exit].setFont(font_);
    menuElements_[MenuElement_Exit].setFillColor(sf::Color::White);
    menuElements_[MenuElement_Exit].setString("Exit");
}

void MainMenu::draw(sf::RenderWindow& window)
{
    const sf::Vector2f& realSize = window.mapPixelToCoords(sf::Vector2i(window.getSize().x, window.getSize().y));
    placeAccordingToSize(realSize);
    for (const auto menuElement : menuElements_)
    {
        window.draw(menuElement);
    }
}

void MainMenu::moveUp()
{
    menuElements_[activeEntry_].setFillColor(sf::Color::White);
    activeEntry_ = MenuElement((MenuElement_Count + activeEntry_ - 1) % MenuElement_Count);
    menuElements_[activeEntry_].setFillColor(sf::Color::Red);
}

void MainMenu::moveDown()
{
    menuElements_[activeEntry_].setFillColor(sf::Color::White);
    activeEntry_ = MenuElement((activeEntry_ + 1) % MenuElement_Count);
    menuElements_[activeEntry_].setFillColor(sf::Color::Red);
}

MainMenu::MenuElement MainMenu::selectEntry()
{
    return activeEntry_;
}

void MainMenu::placeAccordingToSize(const sf::Vector2f size)
{
    menuElements_[MenuElement_Start].setPosition(sf::Vector2f(size.x / 2, size.y / (MenuElement_Count + 1) * 1));
    menuElements_[MenuElement_Options].setPosition(sf::Vector2f(size.x / 2, size.y / (MenuElement_Count + 1) * 2));
    menuElements_[MenuElement_Exit].setPosition(sf::Vector2f(size.x / 2, size.y / (MenuElement_Count + 1) * 3));
}

}  // namespace mainmenu
}  // namespace gamestates
}  // namespace game