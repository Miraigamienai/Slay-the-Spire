#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Camfire_bubble_effect final:public Effects
{
public:
    Camfire_bubble_effect(float x,float y,bool large,const float &offset_y);
    ~Camfire_bubble_effect()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float x,y;
    int img_type;
    float angle_speed,angle;
    float start_duration;
    bool flip_x,flip_y;
    const float &out_offset_y;
};
}