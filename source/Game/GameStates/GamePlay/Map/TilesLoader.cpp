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

sf::Color tileTypeToColor(const Tile::Type type)
{
    switch (type)
    {
        case Tile::Type::Land: return sf::Color(8, 170, 0);
        case Tile::Type::Path: return sf::Color(100, 10, 10);
        case Tile::Type::Start: return sf::Color(8, 200, 0);
        case Tile::Type::Finish: return sf::Color(130, 10, 10);
        default : return sf::Color::Red;
    }
}

Tile::Type charToTileType(const char c)
{
    switch (c)
    {
        case 'L': return Tile::Type::Land;
        case 'P': return Tile::Type::Path;
        case 'S': return Tile::Type::Start;
        case 'F': return Tile::Type::Finish;
        default : return Tile::Type::Land;
    }
}

sf::RectangleShape createShape(const Tile::Type type, const unsigned size, const sf::Vector2i& centre)
{
    sf::RectangleShape rect;
    float offset = size /2;
    rect.setSize(sf::Vector2f(size, size));
    rect.setPosition(sf::Vector2f(centre.x - offset, centre.y - offset));
    rect.setFillColor(tileTypeToColor(type));

    return rect;
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
            const Tile::Type type = tileTypes[i][j];
            const sf::Vector2i centre = sf::Vector2i(x, y);
            const sf::RectangleShape rect = createShape(type, TILE_SIZE, centre);
            tiles.emplace_back(type, TILE_SIZE, centre, false, rect);
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