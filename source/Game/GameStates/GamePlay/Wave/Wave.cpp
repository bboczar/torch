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
    const WaveId id,
    const std::vector<sf::Vector2i>& path,
    const sf::Texture& mobTexture,
    const sf::Texture& projectileTexture)
    : id_(id)
    , path_(path)
    , mobTexture_(mobTexture)
    , projectileTexture_(projectileTexture)
{
    mobs_.emplace_back(1, id_, path_, mobTexture_);
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

    dropRetiredProjectiles();
}

bool Wave::cleared() const
{
    return std::none_of(mobs_.begin(), mobs_.end(), [](const Mob& m){ return m.alive(); })
        and std::none_of(projectiles_.begin(), projectiles_.end(), [](const Projectile& p){ return p.alive(); });
}

void Wave::requestProjectile(Mob& target, const sf::Vector2i& position)
{
    projectiles_.emplace_back(target.id(), position, projectileTexture_,
        std::bind(&Wave::getMobById, this, std::placeholders::_1));
}

std::vector<Mob>& Wave::getMobs()
{
    return mobs_;
}

void Wave::dropRetiredProjectiles()
{
    std::erase_if(projectiles_, [](const Projectile& p){ return !p.alive(); });
}

// TODO: should not be unsafe but make itr optional
Mob& Wave::getMobById(const MobId mobId)
{
    return *std::ranges::find_if(mobs_, [mobId](const Mob& m){ return m.id() == mobId; });
}

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game