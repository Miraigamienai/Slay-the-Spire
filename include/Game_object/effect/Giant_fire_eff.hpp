#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Giant_fire_eff final:public Effects
{
public:
    Giant_fire_eff();
    ~Giant_fire_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const int img_type;
    float x, y;
    const float speed_x, speed_y;
    const float angle;
    const bool flip_x;
    float delay_timer;
    const float target_a;
    static constexpr float DUR=1.5F;
};
}