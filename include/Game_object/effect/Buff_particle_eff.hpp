#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"

namespace Effect{
class Buff_particle_eff final:public Effects,public Abstraction::Reusable<Buff_particle_eff>
{
public:
    Buff_particle_eff(float x, float y)noexcept(noexcept(Initial(x, y))){Initial(x, y);}
    ~Buff_particle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(float x, float y);
private:
    float x, y;
    float speed_y;
    float angle;
    int img_type;

    static constexpr float DUR = 0.5F;
};
}