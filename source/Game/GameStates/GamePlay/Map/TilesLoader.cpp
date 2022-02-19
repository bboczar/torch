#include <Game/GameStates/GamePlay/Map/Defaults.hpp>
#include <Game/GameStates/GamePlay/Map/TilesLoader.hpp>

#include <fstream>
#include <iostream>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

namespace
{

Tile::Type charToTileType(const char c)
{
    switch (c)
    {
        case 'L': return Tile::Type::Land;
        case 'P': return Tile::Type::Path;
        default : return Tile::Type::Land;
    }
}

std::vector<Tile::Type> charLineToTileTypeLine(const std::string& charLine)
{
    std::vector<Tile::Type> tileTypeLine;
    tileTypeLine.reserve(charLine.size());
    std::ranges::transform(charLine, std::back_inserter(tileTypeLine), &charToTileType);
    return tileTypeLine;
}

std::vector<Tile> tileTypesToTiles(const std::vector<std::vector<Tile::Type>>& tileTypes)
{
    std::vector<Tile> tiles;

    for (unsigned i = 0; i < tileTypes.size(); i++)
    {
        for (unsigned j = 0; j < tileTypes[i].size(); j++)
        {
            const unsigned x = TILE_SIZE / 2 + TILE_SIZE * j;
            const unsigned y = TILE_SIZE / 2 + TILE_SIZE * i;
            tiles.emplace_back(tileTypes[i][j], TILE_SIZE, sf::Vector2i(x, y), false);
        }
    }

    return tiles;
}

}  // namespace

std::vector<Tile> TilesLoader::get() const
{
    const auto& tileTypes = parseMapFile();
    return tileTypesToTiles(tileTypes);
}

std::vector<std::vector<Tile::Type>> TilesLoader::parseMapFile() const
{
    std::vector<std::vector<Tile::Type>> tileTypes;
    std::ifstream map;

    map.open("resources/map.txt");
    while (map.good() && !map.eof())
    {
        std::string charLine;
        std::getline(map, charLine);

        if (charLine.empty())
        {
            return tileTypes;
        }

        tileTypes.push_back(std::move(charLineToTileTypeLine(charLine)));
    }

    return tileTypes;
}


}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game