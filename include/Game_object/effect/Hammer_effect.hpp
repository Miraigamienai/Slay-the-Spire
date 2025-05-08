#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Hammer_effect final:public Effects
{
public:
    Hammer_effect(float x,float y);
    ~Hammer_effect()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float x,y,angle;
    float scale2;
};
}