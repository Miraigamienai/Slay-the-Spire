#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Flame_particle_eff final:public Effects
{
public:
    Flame_particle_eff(float x, float y);
    ~Flame_particle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const float start_duration;
    const int img_type;
    float x, y;
    const float speed_x; 
    float speed_y;
    const float acceleration_y;
    const float scale_speed;
    const float angle;
    const bool flip_x;
    float delay_time;
};
}