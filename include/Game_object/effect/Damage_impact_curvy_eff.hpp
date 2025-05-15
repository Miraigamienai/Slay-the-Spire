#pragma once

#include <glm/vec2.hpp>
#include <array>

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Damage_impact_curvy_eff final:public Effects
{
public:
    Damage_impact_curvy_eff(glm::vec2 pos, Uint32 color_rgb);
    ~Damage_impact_curvy_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    static constexpr float COLOR_ALPHA=0.25F;
    static constexpr int MAX_VEC_SIZE=31;//static_cast<int>(std::log(0.05F/COLOR_ALPHA)/std::log(0.95F));
    
    std::array<glm::vec2, MAX_VEC_SIZE> pos_vec;
    int now_vec_pos;
    int now_vec_size;
    glm::vec2 pos;
    float start_duration;
    float current_speed;
    float speed_start, speed_target;
    float wave_speed;
    float wave_height;
    float angle;
};
}