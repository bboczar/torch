#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace map
{

class MapConfig
{
public:
    std::vector<sf::Vector2i> getPath();

private:
    void readFromFile();

    std::vector<sf::Vector2i> path_;
};

}  // namespace map
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game