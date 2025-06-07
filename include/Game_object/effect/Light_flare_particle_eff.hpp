#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Light_flare_particle_eff final:public Effects
{
public:
    Light_flare_particle_eff(float x, float y, Uint32 color_rgb);
    ~Light_flare_particle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float x, y;
    float angle;
    float speed;
    float speed_start, speed_target;
    float start_duration;
    float wave_speed, wave_height;
};
}