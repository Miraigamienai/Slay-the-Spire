#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/interface/Reusable.hpp"

namespace Effect{
class Sleep_cover_eff:public Effects,public Interface::Reusable<Sleep_cover_eff>
{
public:
    Sleep_cover_eff()noexcept(noexcept(Initial())){
        Initial();
    }
    ~Sleep_cover_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial()noexcept;
private:
    float start_duration;
    int img_type;
    float angel,angel_speed;
    float x,y;
    float flip_x,flip_y;
    float target_a;
};
}
