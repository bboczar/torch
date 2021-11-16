#include <Game/GameStates/GamePlay/Wave/WaveConfig.hpp>

#include <cassert>
#include <fstream>

namespace game
{
namespace gamestates
{
namespace gameplay
{
namespace wave
{

WaveData WaveConfig::getNextWaveData()
{
    if (!initialised_)
    {
        readFromFile();
    }

    readFromFile();

    const auto waveData = waveDatas_.front();
    waveDatas_.pop();
    return waveData;
}

void WaveConfig::readFromFile()
{
    std::ifstream waveConfig;

    waveConfig.open("resources/wave_config.txt");
    while (waveConfig.good() && !waveConfig.eof())
    {
        unsigned count, hp, speed;
        waveConfig >> count >> hp >> speed;
        waveDatas_.emplace(count, hp, speed); 
    }

    waveConfig.close();

    assert(!waveDatas_.empty() && "No valid wave configuration!"); 
}

}  // namespace wave
}  // namespace gameplay
}  // namespace gamestates
}  // namespace game