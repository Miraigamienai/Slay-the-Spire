#pragma once

#include <memory>
#include "Game_object/top_panel/Basic_panel.hpp"
#include "WindowSize.hpp"
#include "Draw/NumberDrawer.hpp"

namespace TopPanel
{
class Floor_icon final :public Basic_panel
{

public:
    Floor_icon();
    ~Floor_icon()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update(Dungeon::Dungeon_shared &dungeon_shared);

private:
    Draw::NumberDrawer m_font;
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float ICON_W=64.0F*Setting::SCALE,ICON_H=64.0F*Setting::SCALE,
                           ICON_X=150*Setting::SCALE+(88.0F+18.0F+20.0F)*Setting::SCALE+162.0F*Setting::SCALE+154.0F*Setting::SCALE+310.0F*Setting::SCALE,
                           ICON_Y=Setting::WINDOW_HEIGHT-ICON_W,
                           NUM_OFFSET_X=15.0F*Setting::SCALE;
    int current_floor=1;
};
}

