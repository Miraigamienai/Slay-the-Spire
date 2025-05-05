#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/interface/Reusable.hpp"

namespace Effect{
class Camfire_bubble_effect final:public Effects,public Interface::Reusable<Camfire_bubble_effect>
{
public:
    Camfire_bubble_effect(float x,float y,bool large)noexcept(noexcept(this->Initial(x,y,large))){this->Initial(x,y,large);}
    ~Camfire_bubble_effect()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(float x,float y,bool large);
private:
    float x,y;
    int img_type;
    float angle_speed,angle;
    float start_duration;
    bool flip_x,flip_y;
};
}