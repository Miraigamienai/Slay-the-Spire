#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"

//fwd decl
namespace RUtil{
    class Random;
}

namespace Monster{
enum class LooterAction
{
    Mug,
    Lunge,
    SmokeBomb,
    Escape
};
class Looter final:public Abstraction::Monster_move_tracker<1, LooterAction>
{
public:
    Looter(float offset_x, float offset_y, RUtil::Random& rng);
    ~Looter()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    int move_cnt;
    static constexpr float WIDTH=200.0F*Setting::SCALE,
                           HEIGHT=220.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=0.0F;
    static constexpr int MAX_HP=48,
                         MIN_HP=44,
                         MUG_DAMAGE=10,
                         LUNGE_DAMAGE=12,
                         SMOKE_BOMB_BLOCK=6;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}