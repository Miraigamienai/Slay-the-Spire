#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/interface/Reusable.hpp"

namespace Effect{
class Unknown_particle_eff final:public Effects,public Interface::Reusable<Unknown_particle_eff>
{
public:
    Unknown_particle_eff(float x, float y)noexcept(noexcept(Initial(x, y))){Initial(x, y);}
    ~Unknown_particle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(float x, float y);
    
    static bool is_render_back()noexcept{return s_num!=1;}
private:
    float x, y;
    float angle;
    float target_scale;

    static int s_num;
    static constexpr float DUR = 1.5F;
};
}