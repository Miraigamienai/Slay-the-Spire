#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Blurwave_eff final:public Effects
{
public:
    Blurwave_eff(float x, float y, Uint32 color);
    ~Blurwave_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float wait_timer;
    const float speed_start, speed_target;
    float speed;
    float x, y;
    const float angle;
    static constexpr float DUR = 2.0F;
};
}
