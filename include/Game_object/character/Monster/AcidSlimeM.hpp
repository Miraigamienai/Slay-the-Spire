#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class AcidSlimeMAction
{
    CorrosiveSpit,
    Lick,
    Tackle
};
class AcidSlimeM final:public Abstraction::Monster_move_tracker<2, AcidSlimeMAction>
{
public:
    AcidSlimeM(float offset_x, float offset_y, RUtil::Random& rng);
    ~AcidSlimeM()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    static constexpr float WIDTH=170.0F*Setting::SCALE,
                           HEIGHT=130.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=0.0F;
    static constexpr int MAX_HP=32,
                         MIN_HP=28,
                         CORROSIVE_SPIT_DAMAGE=7,
                         TACKLE_DAMAGE=10;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{30.0F, 30.0F, 40.0F});
};
}