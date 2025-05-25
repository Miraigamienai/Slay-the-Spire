#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Exhaust_ember_eff final:public Effects
{
public:
    Exhaust_ember_eff(float x, float y);
    ~Exhaust_ember_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const int img_type;
    float x, y;
    const float speed_x, speed_y;
    float angle;
    const float angle_speed;
    const float target_scale;
    float start_duration;
};
}