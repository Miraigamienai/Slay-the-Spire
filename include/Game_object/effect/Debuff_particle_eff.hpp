#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"

namespace Effect{
class Debuff_particle_eff final:public Effects,public Abstraction::Reusable<Debuff_particle_eff>
{
public:
    Debuff_particle_eff(float x, float y)noexcept(noexcept(Initial(x, y))){Initial(x, y);}
    ~Debuff_particle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(float x, float y);
    static bool is_render_back()noexcept{return s_img_type==0;}
private:
    float x, y;
    float angle;
    bool clockwise;
    int img_type;

    static int s_img_type;
    static constexpr float DUR = 4.0F;
};
}