#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Fire_burst_particle_eff final:public Effects
{
public:
    Fire_burst_particle_eff(float x, float y);
    ~Fire_burst_particle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const int img_type;
    float x, y;
    float speed_x, speed_y;
    const float angle;
    const float floor;
};
}