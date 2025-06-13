#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"

namespace Monster{
enum class TheGuardianAction
{
    //attack mode
    ChargingUp,
    FierceBash,
    VentSteam,
    Whirlwind,
    //defensive mode
    DefensiveMode,
    RollAttack,
    TwinSlam
};
class TheGuardian final:public Abstraction::Monster_move_tracker<0, TheGuardianAction>
{
public:
    enum class CallType{
        Defensive,
        Offensive,
        Reset
    };
    TheGuardian();
    ~TheGuardian()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
    void Call(CallType call_type, Dungeon::Dungeon_shared &dungeon_shared);
    void damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared, bool deduct_block)override;
    void at_combat_start(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    bool in_defensive_mode;
    int move_cnt;
    int damage_threshold;
    int damage_taken;
    static constexpr float WIDTH=440.0F*Setting::SCALE,
                           HEIGHT=440.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-10.0F*Setting::SCALE;
    static constexpr int HP=240,
                         CHARGING_UP_BLOCK=9,
                         FIERCE_BASH_DAMAGE=32,
                         VENT_DEBUFF_CNT=2,
                         WHIRLWIND_DAMAGE=5,
                         WHIRLWIND_HITS=4,
                         DEFENSIVE_MODE_SHARP=3,
                         ROLL_ATTACK_DAMAGE=9,
                         TWIN_SLAM_DAMAGE=8,
                         DAMAGE_THRESHOLD_START=30,
                         DAMAGE_THRESHOLD_ADD=10;
    static constexpr auto ATK_PATTERN=std::array{TheGuardianAction::Whirlwind, TheGuardianAction::ChargingUp, TheGuardianAction::FierceBash, TheGuardianAction::VentSteam};
    static constexpr auto DEF_PATTERN=std::array{TheGuardianAction::DefensiveMode, TheGuardianAction::RollAttack, TheGuardianAction::TwinSlam};
    static const std::shared_ptr<Draw::ReTexture> &ATK_IMG;
    static const std::shared_ptr<Draw::ReTexture> &DEF_IMG;
};
}