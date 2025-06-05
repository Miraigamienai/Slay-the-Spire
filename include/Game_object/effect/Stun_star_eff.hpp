#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"
#include "RUtil/Some_Math.hpp"

namespace Effect{
class Stun_star_eff final:public Effects,public Abstraction::Reusable<Stun_star_eff>
{
public:
    Stun_star_eff(float x, float y)noexcept(noexcept(Initial(x, y))){Initial(x, y);}
    ~Stun_star_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(float x, float y);
private:
    float x, y;
    float offset_x, offset_y;
    float angle;
    float color_base;

    static constexpr float DUR = 2.0F;
};
}