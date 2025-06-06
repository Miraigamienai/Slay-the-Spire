#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class AcidSlimeLAction
{
    CorrosiveSpit,
    Lick,
    Tackle,
    Split
};
class AcidSlimeL final:public Abstraction::Monster_move_tracker<2, AcidSlimeLAction>
{
public:
    AcidSlimeL(float offset_x, float offset_y, RUtil::Random& rng);
    ~AcidSlimeL()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
    void damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    const float offset_x, offset_y;
    static constexpr float WIDTH=300.0F*Setting::SCALE,
                           HEIGHT=180.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=0.0F;
    static constexpr int MAX_HP=69,
                         MIN_HP=65,
                         CORROSIVE_SPIT_DAMAGE=11,
                         TACKLE_DAMAGE=16;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{30.0F, 30.0F, 40.0F});
};
}