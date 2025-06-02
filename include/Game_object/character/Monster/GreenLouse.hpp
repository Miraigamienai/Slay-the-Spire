#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class GreenLouseAction
{
    SpitWeb,
    Bite
};
class GreenLouse final:public Abstraction::Monster_move_tracker<2, GreenLouseAction>
{
public:
    GreenLouse(float offset_x, float offset_y, RUtil::Random& rng);
    ~GreenLouse()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    const int bite_damage;
    static constexpr float WIDTH=180.0F*Setting::SCALE,
                           HEIGHT=140.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-5.0F*Setting::SCALE;
    static constexpr int MAX_HP=17,
                         MIN_HP=11,
                         MIN_DAMAGE=5,
                         MAX_DAMAGE=7;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{25.0F, 75.0F});
};
}
