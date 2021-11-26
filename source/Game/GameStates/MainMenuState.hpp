#pragma once

#include "SFML/Audio.hpp"
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
    ~MainMenuState();
    DesiredState handleEvents() final;
    void update(const float) final;
    void draw() final;
    GameStateType type() const final;
    void resume() final;
    void pause() final;

private:
    DesiredState handleKeyPressed(const sf::Event event);
    DesiredState resolveState(mainmenu::MainMenu::MenuElement entry);

    sf::RenderWindow& window_;
    sf::Music music_;

    mainmenu::MainMenu menu_;
};

}  // namespace gamestates
}  // namespace game