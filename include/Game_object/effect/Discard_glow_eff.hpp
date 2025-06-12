#pragma once

#include <glm/vec2.hpp>

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Discard_glow_eff final:public Effects
{
public:
    Discard_glow_eff(bool is_above);
    ~Discard_glow_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void set_offset(float offset_x, float offset_y){
        this->offset_x=offset_x;
        this->offset_y=offset_y;
    }
private:
    const int img_type;
    glm::vec2 pos;
    const float start_duration;
    const float scale_jitter;
    const float speed_y;
    const bool is_additive;
    const float angle_speed;
    float offset_x, offset_y;
    float angle;
};
}
