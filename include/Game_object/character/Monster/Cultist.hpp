#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"

namespace Monster{
enum class CultistAction
{
    Incantation,
    DarkStrike
};
class Cultist final:public Abstraction::Monster_move_tracker<1, CultistAction>
{
public:
    Cultist(float offset_x, float offset_y, RUtil::Random& rng);
    ~Cultist()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(RUtil::Random &ai_rng, const Power::Power_group &player_powers) override;
private:
    bool first_move;
    static constexpr float WIDTH=230.0F*Setting::SCALE,
                           HEIGHT=240.0F*Setting::SCALE,
                           HB_OFFSET_X=-8.0F*Setting::SCALE,
                           HB_OFFSET_Y=10.0F*Setting::SCALE;
    static constexpr int MAX_HP=54,
                         MIN_HP=48,
                         DARK_STRIKE_DAMAGE=6;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}