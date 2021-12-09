#pragma once

#include <queue>

#include <SFML/Graphics.hpp>

#include <Game/Traits/DrawingObject.hpp>
#include <Game/GameStates/GamePlay/Map/Background.hpp>
#include <Game/GameStates/GamePlay/Map/MapConfig.hpp>
#include <Game/GameStates/GamePlay/Map/Tiles.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

class Map : public traits::DrawingObject
{
public:
    Map();
    virtual void draw(sf::RenderWindow& window) final;
    MaybeLocation requestBuildLocation(const sf::Vector2i& point);
    void markOccupied(const sf::Vector2i& point);
    std::queue<sf::Vector2i> getPath();

private:
    map::Backgorund background_;
    map::MapConfig mapConfig_;
    map::Tiles tiles_;

    sf::Texture backgroundTexture_;
};

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game