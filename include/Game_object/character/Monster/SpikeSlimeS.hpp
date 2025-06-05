#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Monster{
enum class SpikeSlimeSAction
{
    Tackle
};
class SpikeSlimeS final:public Abstraction::Monster_move_tracker<0, SpikeSlimeSAction>
{
public:
    SpikeSlimeS(float offset_x, float offset_y, RUtil::Random& rng);
    ~SpikeSlimeS()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override{
        set_move(SpikeSlimeSAction::Tackle, nullptr, Intent::attack, TACKLE_DAMAGE, dungeon_shared.player->get_powers());
    }
private:
    static constexpr float WIDTH=130.0F*Setting::SCALE,
                           HEIGHT=100.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-24.0F*Setting::SCALE;
    static constexpr int MAX_HP=14,
                         MIN_HP=10,
                         TACKLE_DAMAGE=5;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}