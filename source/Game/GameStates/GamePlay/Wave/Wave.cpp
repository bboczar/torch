#include <Game/GameStates/GamePlay/Wave/Wave.hpp>

#include <cassert>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace wave
{

Wave::Wave(
    const Id id,
    const std::vector<sf::Vector2i>& path,
    const sf::Texture& mobTexture,
    const sf::Texture& projectileTexture)
    : id_(id)
    , path_(path)
    , mobTexture_(mobTexture)
    , projectileTexture_(projectileTexture)
{
    mobs_.emplace_back(id_, path_, mobTexture_);
}

void Wave::draw(sf::RenderWindow& window)
{
    for (auto& mob : mobs_)
    {
        mob.draw(window);
    }

    for (auto& projectile : projectiles_)
    {
        projectile.draw(window);
    }
}

void Wave::update(const float deltaTimeSec)
{
    if (cleared())
    {
        return;
    }

    for (auto& mob : mobs_)
    {
        mob.update(deltaTimeSec);
    }

    for (auto& projectile : projectiles_)
    {
        projectile.update(deltaTimeSec);
    }

    // dropDeadMobs();
}

bool Wave::cleared() const
{
    return std::none_of(mobs_.begin(), mobs_.end(), [](const Mob& m){ return m.alive(); })
        and std::none_of(projectiles_.begin(), projectiles_.end(), [](const Projectile& p){ return p.alive(); });
}

void Wave::requestProjectile(Mob& target, const sf::Vector2i& position)
{
    projectiles_.emplace_back(target, position, projectileTexture_);
}

std::vector<Mob>& Wave::getMobs()
{
    return mobs_;
}


// void Wave::dropDeadMobs()
// {
//     mobs_.erase(
//         std::remove_if(mobs_.begin(), mobs_.end(), [](const Mob& m){ return !m.alive(); }),
//         mobs_.end()
//     );
// }

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game