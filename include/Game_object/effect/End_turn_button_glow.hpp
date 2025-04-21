#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/interface/Reusable.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class ReTexture;
}

namespace Effect{
class End_turn_button_glow final:public Effects,public Interface::Reusable<End_turn_button_glow>
{
public:
    End_turn_button_glow(const float &button_x,const float &button_y)noexcept{
        Initial(button_x,button_y);
    }
    ~End_turn_button_glow()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(const float &button_x,const float &button_y)noexcept{
        this->button_x=&button_x;
        this->button_y=&button_y;
        this->duration=2.0F;
        this->color_a=1.0F;
        this->is_done=false;
        this->scale=Setting::SCALE;
    }
private:
    const float *button_x,*button_y;
    static const std::shared_ptr<Draw::ReTexture> img;
};
}