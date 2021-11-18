#include <Game/GameStates/GamePlay/Wave/Wave.hpp>

#include <cassert>
#include <iostream>

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
    const unsigned mobCount,
    const sf::Texture& mobTexture,
    const sf::Texture& projectileTexture)
    : id_(id)
    , path_(path)
    , mobSpawnCooldown_(sf::seconds(1))
    , mobIdCounter_(0)
    , spawnedMobsCount_(0)
    , mobCount_(mobCount)
    , mobTexture_(mobTexture)
    , projectileTexture_(projectileTexture)
{
    std::cout << "Spawning wave with " << mobCount_ << " mobs" <<  std::endl; 
    mobSpawnClock_.restart();
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

    if (not fullySpawned() && timeToSpawnMob())
    {
        std::cout << "Spawn mob" << std::endl; 
        spawnMob();
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
    return fullySpawned()
        and std::none_of(mobs_.begin(), mobs_.end(), [](const Mob& m){ return m.alive(); })
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

void Wave::spawnMob()
{
    mobs_.emplace_back(mobIdCounter_, id_, path_, mobTexture_);
    mobIdCounter_++;
    spawnedMobsCount_++;
    mobSpawnClock_.restart();
}

bool Wave::timeToSpawnMob() const
{
    const auto& elapsedTimeSec = mobSpawnClock_.getElapsedTime();
    return elapsedTimeSec >= mobSpawnCooldown_;
}

bool Wave::fullySpawned() const
{
    return spawnedMobsCount_ >= mobCount_;
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