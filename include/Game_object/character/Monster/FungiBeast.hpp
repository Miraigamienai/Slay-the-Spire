#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class FungiBeastAction
{
    Bite,
    Grow
};
class FungiBeast final:public Abstraction::Monster_move_tracker<2, FungiBeastAction>
{
public:
    FungiBeast(float offset_x, float offset_y, RUtil::Random& rng);
    ~FungiBeast()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:                 
    static constexpr float WIDTH=260.0F*Setting::SCALE,
                           HEIGHT=170.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-16.0F*Setting::SCALE;
    static constexpr int MAX_HP=28,
                         MIN_HP=22,
                         BITE_DAMAGE=6;

    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{60.0F, 40.0F});
};
}