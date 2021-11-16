#pragma once

#include <queue>

#include <SFML/Graphics.hpp>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace wave
{

struct WaveData
{
    const unsigned mobCount;
    const unsigned mobHp;
    const unsigned mobSpeed;
};

class WaveConfig
{
public:
    WaveData getNextWaveData();

private:
    void readFromFile();

    bool initialised_;
    std::queue<WaveData> waveDatas_;
};

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game