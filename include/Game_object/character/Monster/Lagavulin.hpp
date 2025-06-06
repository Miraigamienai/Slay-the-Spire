#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class LagavulinAction
{
    Attack,
    SiphonSoul,
    METALLICIZE
};
class Lagavulin final:public Abstraction::Monster_move_tracker<2, LagavulinAction>
{
public:
    Lagavulin(float offset_x, float offset_y, RUtil::Random& rng);
    ~Lagavulin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    bool first_move,is_awake=false;
    static constexpr float WIDTH=260.0F*Setting::SCALE,
                           HEIGHT=170.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-25.0F*Setting::SCALE;
    static constexpr int MAX_HP=111,
                         MIN_HP=109,
                         ATTACK_DAMAGE=18,
                         SIPHONSOUL_DEXTERITY=-1,
                         SIPHONSOUL_STRENGTH=-1,
                         METALLICIZE_BLOCK=8;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{0.0F,33.0F,67.0F});
};
}