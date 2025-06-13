#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"

namespace Monster{
enum class SlimeBossAction
{
    GoopSpray,
    Preparing,
    Slam,
    Split
};
class SlimeBoss final:public Abstraction::Monster_move_tracker<0, SlimeBossAction>
{
public:
    SlimeBoss();
    ~SlimeBoss()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
    void damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared, bool deduct_block)override;
private:
    int move_cnt;
    static constexpr std::array<SlimeBossAction, 3> pattern=std::array{SlimeBossAction::GoopSpray, SlimeBossAction::Preparing, SlimeBossAction::Slam};
    static constexpr float WIDTH=400.0F*Setting::SCALE,
                           HEIGHT=350.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-30.0F*Setting::SCALE;
    static constexpr int HP=140,
                         SLAM_DAMAGE=35,
                         SPLIT_CNT=-1;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}