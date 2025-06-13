#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class SpikeSlimeLAction
{
    FlameTackle,
    Lick,
    Split
};
class SpikeSlimeL final:public Abstraction::Monster_move_tracker<2, SpikeSlimeLAction>
{
public:
    SpikeSlimeL(float offset_x, float offset_y, RUtil::Random& rng);
    SpikeSlimeL(float offset_x, float offset_y, int HP);
    ~SpikeSlimeL()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
    void damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared, bool deduct_block)override;
private:
    const float offset_x, offset_y;
    const int current_max_hp;
    static constexpr float WIDTH=300.0F*Setting::SCALE,
                           HEIGHT=180.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-30.0F*Setting::SCALE;
    static constexpr int MAX_HP=70,
                         MIN_HP=64,
                         FLAME_TACKLE_DAMAGE=16;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{30.0F, 70.0F});
};
}