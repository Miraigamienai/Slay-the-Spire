#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"

//fwd decl
namespace RUtil{
    class Random;
}

namespace Monster{
enum class WizardGremlinAction
{
    UltimateBlast,
    Charging
};
class WizardGremlin final:public Abstraction::Monster_move_tracker<0, WizardGremlinAction>
{
public:
    WizardGremlin(float offset_x, float offset_y, RUtil::Random& rng);
    ~WizardGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    int charging_cnt;
    static constexpr float WIDTH=130.0F*Setting::SCALE,
                           HEIGHT=180.0F*Setting::SCALE,
                           HB_OFFSET_X=40.0F*Setting::SCALE,
                           HB_OFFSET_Y=-5.0F*Setting::SCALE;
    static constexpr int MAX_HP=25,
                         MIN_HP=21,
                         ULTIMATE_BLAST=25;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}