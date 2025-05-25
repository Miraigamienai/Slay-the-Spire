#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Exhaust_blur_eff final:public Effects
{
public:
    Exhaust_blur_eff(float x, float y);
    ~Exhaust_blur_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const bool img_type;
    float x, y;
    const float speed_y;
    float angle;
    const float angle_speed;
    const float target_scale;
    const float start_duration;
};
}