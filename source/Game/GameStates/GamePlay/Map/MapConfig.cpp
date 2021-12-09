#include <Game/GameStates/GamePlay/Map/MapConfig.hpp>

#include <cassert>
#include <fstream>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

std::queue<sf::Vector2i> MapConfig::getPath()
{
    if (!path_.empty())
    {
        return path_;
    }

    readFromFile();

    return path_;
}

void MapConfig::readFromFile()
{
    std::ifstream mapConfig;

    mapConfig.open("resources/map_config.txt");
    while (mapConfig.good() && !mapConfig.eof())
    {
        int x, y;
        mapConfig >> x >> y;
        path_.push(sf::Vector2i(x, y)); 
    }

    mapConfig.close();

    assert(!path_.empty() && "No valid points in the map's path"); 
}

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game