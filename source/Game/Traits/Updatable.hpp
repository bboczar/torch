#pragma once

namespace game
{
namespace traits
{

class Updatable
{
public:
    virtual void update() = 0;
};

}  // namespace traits
}  // namespace game