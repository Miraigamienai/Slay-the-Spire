#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"

namespace Effect{
class Flying_spike_eff final:public Effects, public Abstraction::Reusable<Flying_spike_eff>
{
public:
    Flying_spike_eff(float x, float y, float speed_x, float speed_y, float angle, Uint32 color){
        Initial(x,y,speed_x,speed_y,angle,color);
    }
    ~Flying_spike_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(float x, float y, float speed_x, float speed_y, float angle, Uint32 color);
private:
    float x,y;
    float speed_x,speed_y;
    float angle;
    static constexpr float DUR=0.75F;
};
}