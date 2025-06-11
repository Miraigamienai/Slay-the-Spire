#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"

//fwd decl
namespace RUtil{
    class Random;
}

namespace Monster{
enum class SentryAction
{
    Beam,
    Bolt
};
class Sentry final:public Abstraction::Monster_move_tracker<0, SentryAction>
{
public:
    Sentry(float offset_x, float offset_y, RUtil::Random& rng, bool start_with_bolt);
    ~Sentry()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
    void at_combat_start(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    bool is_current_bolt;
    static constexpr float WIDTH=180.0F*Setting::SCALE,
                           HEIGHT=310.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-5.0F*Setting::SCALE;
    static constexpr int MAX_HP=42,
                         MIN_HP=38,
                         BEAM_DAMAGE=9,
                         BOLT_SHUFFLENUM=2;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}