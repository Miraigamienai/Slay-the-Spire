#pragma once

#include "Game_object/character/Player.hpp"

namespace EnergyOrb{
class Energy_orb{
public:
    Energy_orb()=default;
    virtual ~Energy_orb()=default;
    virtual void update(float energy)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2, float energy, float panel_x, float panel_y)const=0;
protected:
    static constexpr float ORB_SCALE=1.15F*Setting::SCALE;
};
}