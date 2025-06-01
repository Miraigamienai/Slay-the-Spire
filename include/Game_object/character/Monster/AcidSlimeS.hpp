#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class AcidSlimeSAction
{
    Lick,
    Tackle,
    None
};
class AcidSlimeS final:public Abstraction::Monster_move_tracker<2, AcidSlimeSAction>
{
public:
    AcidSlimeS(float offset_x, float offset_y, RUtil::Random& rng);
    ~AcidSlimeS()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(RUtil::Random &ai_rng, const Power::Power_group &player_powers) override;
private:
    static constexpr float WIDTH=130.0F*Setting::SCALE,
                           HEIGHT=100.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-4.0F*Setting::SCALE;
    static constexpr int MAX_HP=12,
                         MIN_HP=8,
                         TACKLE_DAMAGE=3;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{50.0F,50.0F});
};
}