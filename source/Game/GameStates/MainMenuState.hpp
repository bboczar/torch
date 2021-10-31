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
    std::optional<GameStateType> handleEvents() final;
    void update() final;
    void draw() final;
private:
    std::optional<GameStateType> handleKeyPressed(const sf::Event event);
    std::optional<GameStateType> resolveState(mainmenu::MainMenu::MenuElement entry);

    sf::RenderWindow& window_;

    mainmenu::MainMenu menu_;
};

}  // namespace gamestates
}  // namespace game