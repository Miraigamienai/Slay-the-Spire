#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"

namespace EffectGen{
class Fire_ball_gen final:public Effect_gen
{
public:
    Fire_ball_gen(float start_x, float start_y, float target_x, float target_y);
    ~Fire_ball_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    float x, y;
    float start_x, start_y;
    float target_x, target_y;
    float gen_timer;
    static constexpr float DUR=0.5F;
};
}