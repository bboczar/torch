#include <Game/GameStates/GamePlay/Map/Defaults.hpp>
#include <Game/GameStates/GamePlay/Map/Tiles.hpp>
#include <Game/GameStates/GamePlay/Map/TilesLoader.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

Tiles::Tiles()
: tiles_(TilesLoader().get())
{
    if (tiles_.empty())
    {
        setDefaultTiles();
    }
}

void Tiles::setDefaultTiles()
{
    for (unsigned x = TILE_SIZE / 2; x < MAP_WIDTH; x += TILE_SIZE)
    {
        for (unsigned y = TILE_SIZE / 2; y < MAP_HEIGHT; y += TILE_SIZE)
        {
            tiles_.emplace_back(Tile::Type::Land, TILE_SIZE, sf::Vector2i(x, y), false);
        }
    }
}

MaybeLocation Tiles::requestBuildLocation(const sf::Vector2i& point) 
{
    const Tile& tile = getTileIncluding(point);
    return tile.type == Tile::Type::Land and not tile.occupied
        ? MaybeLocation(tile.centre)
        : MaybeLocation();
}

void Tiles::markOccupied(const sf::Vector2i& point)
{
    Tile& tile = getTileIncluding(point);
    tile.occupied = true;
}

Tile& Tiles::getTileIncluding(const sf::Vector2i& point)
{
    return *std::ranges::find_if(
        tiles_, [&point, this](const Tile& t) { return tileIncludes(t, point); }
    );
}

bool Tiles::tileIncludes(const Tile& tile, const sf::Vector2i& point) const
{
    const int halfSize = tile.size / 2;
    return ((tile.centre.x - halfSize) < point.x and (tile.centre.x + halfSize) > point.x)
        and ((tile.centre.y - halfSize) < point.y and (tile.centre.y + halfSize) > point.y);
}

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game