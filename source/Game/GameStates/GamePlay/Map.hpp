#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <Game/GameStates/GamePlay/Background.hpp>
#include <Game/GameStates/GamePlay/Mob.hpp>
#include <Game/GameStates/GamePlay/Tower.hpp>
#include <Game/Traits/DrawingObject.hpp>
#include <Game/Traits/Updatable.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{

class Map : public traits::DrawingObject, traits::Updatable
{
public:
    Map();

    virtual void draw(sf::RenderWindow& window) final;
    virtual void update(const float deltaTimeSec) final;

private:
    void dropDeadMobs();

    std::vector<Mob> mobs_;
    std::vector<Tower> towers_;
    Backgorund background_;
};

}  // namespace gameplay
}  // namespace gamestates
}  // namespace game