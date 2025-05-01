#pragma once

#include <SDL_stdinc.h>//Uint32

#include "Game_object/effect/Effects.hpp"
#include "Game_object/interface/Reusable.hpp"

namespace Effect{
class Vertical_aura:public Effects,public Interface::Reusable<Vertical_aura>
{
public:
    Vertical_aura(Uint32 color, float x, float y){Initial(color,x,y);}
    ~Vertical_aura()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(Uint32 color, float x, float y);
private:
    float x,y;
    float speed_y, wait_timer;
};
}
