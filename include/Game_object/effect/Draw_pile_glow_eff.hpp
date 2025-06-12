#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Draw_pile_glow_eff final:public Effects
{
public:
    Draw_pile_glow_eff();
    ~Draw_pile_glow_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void set_offset(float offset_x, float offset_y){
        this->offset_x=offset_x;
        this->offset_y=offset_y;
    }
private:
    const int img_type;
    const float start_duration;
    float x, y;
    float speed_x, speed_y;
    const bool flip_x, flip_y;
    const float angle_speed;
    float offset_x, offset_y;
    float angle;
};
}
