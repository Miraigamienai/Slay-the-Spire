#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Monster{
enum class SneakyGremlinAction
{
    Puncture
};
class SneakyGremlin final:public Abstraction::Monster_move_tracker<0, SneakyGremlinAction>
{
public:
    SneakyGremlin(float offset_x, float offset_y, RUtil::Random& rng);
    ~SneakyGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override{
        set_move(SneakyGremlinAction::Puncture, nullptr, Intent::attack, PUNCTURE_DAMAGE, dungeon_shared.player->get_powers());
    }
private:
    static constexpr float WIDTH=120.0F*Setting::SCALE,
                           HEIGHT=160.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=0.0F;
    static constexpr int MAX_HP=14,
                         MIN_HP=10,
                         PUNCTURE_DAMAGE=9;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}