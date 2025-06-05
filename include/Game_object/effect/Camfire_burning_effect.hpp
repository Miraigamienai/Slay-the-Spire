#pragma once

#include <SDL_stdinc.h>

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"

namespace Effect{
class Camfire_burning_effect final:public Effects,public Abstraction::Reusable<Camfire_burning_effect>
{
public:
    Camfire_burning_effect(Uint32 color_rgb)noexcept(noexcept(this->Initial(color_rgb))){this->Initial(color_rgb);}
    ~Camfire_burning_effect()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(Uint32 color_rgb);
private:
    float x,y;
    float speed_x, speed_y1, speed_y2;
    float start_duration;
    int img_type;
    bool flip_x;
    float target_a;
    float delay_timer;
    float angle;
};
}