#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class BlueSlaverAction
{
    Stab,
    Rake
};
class BlueSlaver final:public Monsters
{
public:
    BlueSlaver(float offsetX,float offsetY);
    ~BlueSlaver ()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static constexpr int WIDTH=320.0F*Setting::SCALE,
                         HEIGHT=230.0F*Setting::SCALE;
    static constexpr int MAX_HP=50,
                         MIN_HP=46,
                         STAB_DAMAGE=12,
                         RAKE_DAMAGE=7;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr auto dist=RUtil::make_weighted_index_picker(std::array{60.0F,40.0F});
};
}