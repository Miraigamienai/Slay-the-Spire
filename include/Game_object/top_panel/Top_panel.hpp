#pragma once

#include <memory>
#include "Draw/Draw_2D.hpp"
#include "Game_object/top_panel/Deck_icon.hpp"
#include "Game_object/top_panel/Floor_icon.hpp"
#include "Game_object/top_panel/Gold_bag_icon.hpp"
#include "Game_object/top_panel/Heart_icon.hpp"
#include "Game_object/top_panel/Map_icon.hpp"
#include "Game_object/top_panel/Setting_icon.hpp"
#include "WindowSize.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
namespace TopPanel
{
class Top_panel
{

public:
    Top_panel();
    ~Top_panel()=default;

    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update(Dungeon::Dungeon_shared &dungeon_shared);
private:
    Deck_icon deck;
    Floor_icon floor;
    Map_icon map;
    Gold_bag_icon goldBag;
    Heart_icon heart;
    Setting_icon setting;
    static const std::shared_ptr<Draw::ReTexture> &bar_img;
    //,&deck,&floor,&map,&goldBag,&heart,&setting;
    static constexpr float bar_x=0.0F,bar_y=Setting::WINDOW_HEIGHT-128.0F*Setting::SCALE,bar_h=128.0F*Setting::SCALE,bar_w=Setting::WINDOW_WIDTH;  

};
}

