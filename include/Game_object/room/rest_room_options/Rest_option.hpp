#pragma once

#include "Game_object/room/rest_room_options/Options.hpp"

namespace Room{
namespace Option{
class Rest_option final:public Options
{
public:
    Rest_option(int player_max_hp,Uint32 dungeon_fade_color);
    ~Rest_option()override=default;
    void chile_label_render(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 font_color)const override;
    void chile_description_render(const std::shared_ptr<Draw::Draw_2D> &r2,float font_color_a)const override;
    void take_reward(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    Uint32 dungeon_fade_color;
    int heal_amount;
};   
}
}