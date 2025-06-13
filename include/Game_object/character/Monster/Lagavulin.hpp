#pragma once

#include <array>

#include "Game_object/abstraction/Monster_move_tracker.hpp"

//fwd decl
namespace RUtil{
    class Random;
}

namespace Monster{
enum class LagavulinAction
{
    Attack,
    SiphonSoul,
    Sleep,
    Stun
};
class Lagavulin final:public Abstraction::Monster_move_tracker<0, LagavulinAction>
{
public:
    Lagavulin(RUtil::Random& rng);
    ~Lagavulin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
    void at_combat_start(Dungeon::Dungeon_shared &dungeon_shared) override;
    void Call(Dungeon::Dungeon_shared &dungeon_shared);
    void damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared, bool deduct_block)override;
private:
    int sleep_cnt;
    bool is_awake;
    int move_cnt;
    static constexpr float WIDTH=320.0F*Setting::SCALE,
                           HEIGHT=220.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-25.0F*Setting::SCALE;
    static constexpr int MAX_HP=111,
                         MIN_HP=109,
                         ATTACK_DAMAGE=18,
                         SIPHONSOUL_DEBUFF_NUM=-1,
                         METALLICIZE_BLOCK=8;
    static constexpr auto PATTERN=std::array{LagavulinAction::Attack, LagavulinAction::Attack, LagavulinAction::SiphonSoul};
    static const std::shared_ptr<Draw::ReTexture> &AWAKE_IMG, &SLEEP_IMG;
};
}