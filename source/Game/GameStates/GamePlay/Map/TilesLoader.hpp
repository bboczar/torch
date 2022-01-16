#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Map/Tile.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

class TilesLoader
{
public:
    std::vector<Tile> get() const;

private:
    std::vector<std::vector<Tile::Type>> parseMapFile() const;
};

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game