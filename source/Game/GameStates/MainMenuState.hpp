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
    MainMenuState();
    bool handleEvent(sf::Event event) final;
    void update() final;
    void draw(sf::RenderWindow& window) final;
private:
    mainmenu::MainMenu menu_;
};

}  // namespace gamestates
}  // namespace game