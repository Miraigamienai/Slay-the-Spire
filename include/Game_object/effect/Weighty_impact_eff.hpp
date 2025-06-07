#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Weighty_impact_eff:public Effects
{
public:
    Weighty_impact_eff(float x, float y, float color_r, float color_b)noexcept;
    ~Weighty_impact_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const float x;
    float y;
    const float r, b;
    const float angle;
    const float target_y;

    static constexpr float DUR=1.0F;
};
}
