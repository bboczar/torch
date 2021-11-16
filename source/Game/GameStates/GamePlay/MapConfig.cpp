#include <Game/GameStates/GamePlay/MapConfig.hpp>

#include <cassert>
#include <fstream>

namespace game
{
namespace gamestates
{
namespace gameplay
{

std::vector<sf::Vector2i> MapConfig::getPath()
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
        path_.push_back(sf::Vector2i(x, y)); 
    }

    mapConfig.close();

    assert(!path_.empty() && "No valid points in the map's path"); 

    std::reverse(path_.begin() ,path_.end());
}

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game