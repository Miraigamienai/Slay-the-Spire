#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class GremlinNobAction
{
    Bellow,
    Rush,
    SkullBash
};
class GremlinNob final:public Abstraction::Monster_move_tracker<2, GremlinNobAction>
{
public:
    GremlinNob(float offset_x, float offset_y, RUtil::Random& rng);
    ~GremlinNob()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    bool first_move;
    static constexpr float WIDTH=340.0F*Setting::SCALE,
                           HEIGHT=390.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-25.0F*Setting::SCALE;
    static constexpr int MAX_HP=86,
                         MIN_HP=82,
                         SKULL_BASH_DAMAGE=6,
                         SKULL_BASH_VULNERABLE=2,
                         RUSH_DAMAGE=14,
                         BELLOWS_STRENGTH=2;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{0.0F,33.0F,67.0F});
};
}