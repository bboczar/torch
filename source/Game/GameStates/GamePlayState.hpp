#pragma once

#include <SFML/Graphics.hpp>

#include <Game/GameState.hpp>
#include <Game/GameStates/GamePlay/GamePlay.hpp>

namespace game
{
namespace gamestates
{

class GamePlayState : public GameState
{
public:
    GamePlayState(sf::RenderWindow& window, sf::Font font);
    DesiredState handleEvents() final;
    void update(const float deltaTimeSec) final;
    void draw() final;
    GameStateType type() const final;
private:
    DesiredState handleKeyReleased(const sf::Event event);
    void handleMouseButtonPressed(const sf::Event event);

    gameplay::GamePlay gamePlay_;

    sf::RenderWindow& window_;
    sf::Font font_;
};

}  // namespace gamestates
}  // namespace game