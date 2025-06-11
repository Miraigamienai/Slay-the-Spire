#pragma once

#include <glm/vec2.hpp>

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Small_laser_eff final:public Effects
{
public:
    Small_laser_eff(const glm::vec2 &start_pos,const glm::vec2 &target_pos);
    ~Small_laser_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const float start_x, start_y;
    const float distant;
    const float angle;

    static constexpr float DUR=0.5F;
};
}
