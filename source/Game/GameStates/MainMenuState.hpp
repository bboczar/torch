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
    MainMenuState(sf::RenderWindow& window);
    void handleEvents() final;
    void update() final;
    void draw() final;
private:
    void handleKeyPressed(const sf::Event event);

    sf::RenderWindow& window_;
    mainmenu::MainMenu menu_;
};

}  // namespace gamestates
}  // namespace game