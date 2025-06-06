#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class SpikeSlimeMAction
{
    FlameTackle,
    Lick
};
class SpikeSlimeM final:public Abstraction::Monster_move_tracker<2, SpikeSlimeMAction>
{
public:
    SpikeSlimeM(float offset_x, float offset_y, RUtil::Random& rng);
    SpikeSlimeM(float offset_x, float offset_y, int HP);
    ~SpikeSlimeM()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    static constexpr float WIDTH=170.0F*Setting::SCALE,
                           HEIGHT=130.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-25.0F*Setting::SCALE;
    static constexpr int MAX_HP=32,
                         MIN_HP=28,
                         FLAME_TACKLE_DAMAGE=8;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{30.0F, 70.0F});
};
}