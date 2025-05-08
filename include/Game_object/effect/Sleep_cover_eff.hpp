#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Sleep_cover_eff:public Effects
{
public:
    Sleep_cover_eff();
    ~Sleep_cover_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float start_duration;
    int img_type;
    float angel,angel_speed;
    float x,y;
    float flip_x,flip_y;
    float target_a;
};
}
