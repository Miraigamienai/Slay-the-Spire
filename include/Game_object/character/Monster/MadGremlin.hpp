#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Monster{
enum class MadGremlinAction
{
    Scratch
};
class MadGremlin final:public Abstraction::Monster_move_tracker<0, MadGremlinAction>
{
public:
    MadGremlin(float offset_x, float offset_y, RUtil::Random& rng);
    ~MadGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override{
        set_move(MadGremlinAction::Scratch, nullptr, Intent::attack, SCRATCH_DAMAGE, dungeon_shared.player->get_powers());
    }
private:
    static constexpr float WIDTH=130.0F*Setting::SCALE,
                           HEIGHT=194.0F*Setting::SCALE,
                           HB_OFFSET_X=-4.0F*Setting::SCALE,
                           HB_OFFSET_Y=12.0F*Setting::SCALE;
    static constexpr int MAX_HP=24,
                         MIN_HP=20,
                         SCRATCH_DAMAGE=4;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}