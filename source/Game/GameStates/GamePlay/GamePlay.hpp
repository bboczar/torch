#pragma once

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Map.hpp>
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
    virtual void update(const float deltaTimeSec) final;

private:
    Map map_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game