#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Cleave_eff final:public Effects
{
public:
    Cleave_eff(float x, float y);
    ~Cleave_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float wait_timer;
    float x;
    const float y;
    float angle;
    static constexpr float FADE_IN_TIME = 0.05F;
    static constexpr float FADE_OUT_TIME = 0.4F;
};
}
