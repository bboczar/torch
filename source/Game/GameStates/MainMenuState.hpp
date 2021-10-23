#pragma once

#include <stack>

#include <Game/GameState.hpp>

namespace game
{
namespace gamestates
{

class MainMenuState : public GameState
{
public:
    MainMenuState();
    void handleEvent(sf::Event) final;
    void update() final;
    void draw() final;
};

}  // namespace gamestates
}  // namespace game