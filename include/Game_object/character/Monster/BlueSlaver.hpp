#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class BlueSlaverAction
{
    Stab,
    Rake
};
class BlueSlaver final:public Abstraction::Monster_move_tracker<2, BlueSlaverAction>
{
public:
    BlueSlaver(float offset_x, float offset_y, RUtil::Random& rng);
    ~BlueSlaver()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
private:
    static constexpr float WIDTH=170.0F*Setting::SCALE,
                           HEIGHT=230.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=0.0F;
    static constexpr int MAX_HP=50,
                         MIN_HP=46,
                         STAB_DAMAGE=12,
                         RAKE_DAMAGE=7;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{60.0F, 40.0F});
};
}