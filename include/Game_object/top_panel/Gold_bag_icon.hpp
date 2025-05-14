#pragma once

#include <memory>
#include "Game_object/top_panel/Basic_panel.hpp"
#include "WindowSize.hpp"

namespace TopPanel
{
class Gold_bag_icon final :public Basic_panel
{

public:
    Gold_bag_icon();
    ~Gold_bag_icon()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update(Dungeon::Dungeon_shared &dungeon_shared) override;

private:
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float ICON_W=64.0F*Setting::SCALE,ICON_H=64.0F*Setting::SCALE,
                           ICON_X=150*Setting::SCALE+(88.0F+18.0F+20.0F)*Setting::SCALE+162.0F*Setting::SCALE,
                           ICON_Y=Setting::WINDOW_HEIGHT-ICON_W,
                           TIP_W=120.0F*Setting::SCALE,
                           NUM_OFFSET_X=25.0F*Setting::SCALE;
    Draw::NumberDrawer m_font;
    int current_gold=0;
};
}

