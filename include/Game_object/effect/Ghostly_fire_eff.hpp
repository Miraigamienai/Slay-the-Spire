#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Ghostly_fire_eff final:public Effects
{
public:
    Ghostly_fire_eff(float x, float y, bool is_weak);
    ~Ghostly_fire_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const bool weak;
    const int img_type;
    float x, y;
    const float speed_x, speed_y;
};
}