#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class MapConfig
{
public:
    std::vector<sf::Vector2i> getPath();

private:
    std::vector<sf::Vector2i> path_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game