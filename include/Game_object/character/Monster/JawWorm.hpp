#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class JawWormAction
{
    Chomp,
    Thrash,
    Bellow
};
class JawWorm final:public Abstraction::Monster_move_tracker<2, JawWormAction>
{
public:
    JawWorm(float offset_x, float offset_y, RUtil::Random& rng);
    ~JawWorm()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(RUtil::Random &ai_rng, const Power::Power_group &player_powers) override;
private:
    bool first_move;
    static constexpr float WIDTH=260.0F*Setting::SCALE,
                           HEIGHT=170.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-25.0F*Setting::SCALE;
    static constexpr int MAX_HP=44,
                         MIN_HP=40,
                         CHOMP_DAMAGE=11,
                         THRASH_DAMAGE=7,
                         THRASH_BLOCK=5,
                         BELLOWS_STRENGTH=3,
                         BELLOWS_BLOCK=6;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{25.0F,30.0F,45.0F});
};
}