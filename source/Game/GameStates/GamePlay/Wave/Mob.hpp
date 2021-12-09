#pragma once

#include <queue>

#include <SFML/Graphics.hpp>

#include <Game/Traits/DrawingObject.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace wave
{

using MobId = unsigned;
using WaveId = unsigned;

enum class MobStatus
{
    Alive,
    Killed,
    Destination
};

class Mob : public traits::DrawingObject
{
public:
    Mob(
        const MobId id,
        const WaveId waveId,
        const unsigned hp,
        const unsigned speed,
        const std::queue<sf::Vector2i>& path,
        const sf::Texture& texture);

    virtual void draw(sf::RenderWindow& window) final;
    void update(const float deltaTimeSec);
    void hit(const unsigned damage);

    MobId id() const;
    WaveId waveId() const;
    sf::Vector2i position() const;
    MobStatus status() const;
    bool alive() const;

private:
    void move(const float deltaTimeSec);
    unsigned calcNewPosition(const unsigned current, const unsigned destination, const unsigned distance) const;

    void die();
    void destinationReached();

    MobId id_;
    WaveId waveId_;

    MobStatus status_;
    unsigned heathPoints_;
    unsigned speed_;
    sf::Vector2i position_;
    std::queue<sf::Vector2i> path_;

    sf::Sprite sprite_;
};

using MaybeMobRef = std::optional<std::reference_wrapper<Mob>>;

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game