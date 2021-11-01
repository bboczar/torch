#pragma once

#include <stack>

#include <SFML/Graphics.hpp>

#include <Game/GameState.hpp>
#include <Game/GameStates/MainMenu/MainMenu.hpp>

namespace game
{
namespace gamestates
{

class MainMenuState : public GameState
{
public:
    MainMenuState(sf::RenderWindow& window, sf::Font font);
    DesiredState handleEvents() final;
    void update() final;
    void draw() final;
    GameStateType type() const final;
private:
    DesiredState handleKeyPressed(const sf::Event event);
    DesiredState resolveState(mainmenu::MainMenu::MenuElement entry);

    sf::RenderWindow& window_;

    mainmenu::MainMenu menu_;
};

}  // namespace gamestates
}  // namespace game