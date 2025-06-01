#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"
#include "WindowSize.hpp"

namespace Effect{
class Shield_particle_eff final:public Effects,public Abstraction::Reusable<Shield_particle_eff>
{
public:
    Shield_particle_eff(float x, float y)noexcept(noexcept(Initial(x, y))){Initial(x, y);}
    ~Shield_particle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(float x, float y)noexcept{
        is_done=false;
        duration=DUR;
        color_a=0.0F;
        scale=Setting::SCALE*0.5F;
        this->x=x-32.0F;
        this->y=y-32.0F;
    }
private:
    float x, y;

    static constexpr float DUR = 2.0F;
};
}