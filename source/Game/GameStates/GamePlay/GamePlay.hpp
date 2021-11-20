#pragma once

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Map.hpp>
#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class GamePlay : public traits::DrawingObject
{
public:
    GamePlay(const sf::Font font);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);
    void requestTower(const int x, const int y);

private:
    Map map_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game