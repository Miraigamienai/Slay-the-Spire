#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"

//fwd decl
namespace RUtil{
    class Random;
}

namespace Monster{
enum class ShieldGremlinAction
{
    Protect,
    ShieldBash
};
class ShieldGremlin final:public Abstraction::Monster_move_tracker<1, ShieldGremlinAction>
{
public:
    ShieldGremlin(float offset_x, float offset_y, RUtil::Random& rng);
    ~ShieldGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    static constexpr float WIDTH=120.0F*Setting::SCALE,
                           HEIGHT=200.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=0.0F;
    static constexpr int MAX_HP=15,
                         MIN_HP=12,
                         PROTECT_BLOCK=7,
                         SHIELD_BASH_DAMAGE=6;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}