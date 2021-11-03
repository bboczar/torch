#pragma once

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Background.hpp>
#include <Game/Traits/DrawingObject.hpp>
#include <Game/Traits/Updatable.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class GamePlay : public traits::DrawingObject, traits::Updatable
{
public:
    GamePlay();

    virtual void draw(sf::RenderWindow& window) final;
    virtual void update() final;

private:
    Backgorund background_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game