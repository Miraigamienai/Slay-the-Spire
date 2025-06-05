#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Monster{
enum class FatGremlinAction
{
    Smash
};
class FatGremlin final:public Abstraction::Monster_move_tracker<0, FatGremlinAction>
{
public:
    FatGremlin(float offset_x, float offset_y, RUtil::Random& rng);
    ~FatGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared)override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override{
        set_move(FatGremlinAction::Smash, nullptr, Intent::attack_debuff, SMASH_DAMAGE, dungeon_shared.player->get_powers());
    }
private:
    static constexpr float WIDTH=110.0F*Setting::SCALE,
                           HEIGHT=220.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=0.0F;
    static constexpr int MAX_HP=17,
                         MIN_HP=13,
                         SMASH_DAMAGE=4;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}