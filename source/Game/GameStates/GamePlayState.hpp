#pragma once

#include <SFML/Graphics.hpp>

#include <Game/GameState.hpp>

namespace game
{
namespace gamestates
{

class GamePlayState : public GameState
{
public:
    GamePlayState(sf::RenderWindow& window, sf::Font font);
    DesiredState handleEvents() final;
    void update() final;
    void draw() final;
    GameStateType type() const final;
private:
    DesiredState handleKeyPressed(const sf::Event event);
    DesiredState resolveState();

    sf::RenderWindow& window_;

    sf::Font font_;
    sf::Sprite background_;
    sf::Texture backgroundTexture_;
};

}  // namespace gamestates
}  // namespace game