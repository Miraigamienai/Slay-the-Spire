#pragma once

#include "Game_object/room/rest_room_options/Options.hpp"

namespace Room{
namespace Option{
class Smith_option final:public Options
{
public:
    Smith_option(bool any_card_can_upgrade);
    ~Smith_option()override=default;
    void child_label_render(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 font_color)const override;
    void child_description_render(const std::shared_ptr<Draw::Draw_2D> &r2,float font_color_a)const override;
    void take_reward(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    bool skip_one_frame;
};   
}
}