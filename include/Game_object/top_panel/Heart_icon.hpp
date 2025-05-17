#pragma once

#include <memory>
#include "Game_object/top_panel/Basic_panel.hpp"
#include "Draw/NumberDrawer.hpp"
#include "WindowSize.hpp"

namespace TopPanel
{
class Heart_icon final :public Basic_panel
{

public:
    Heart_icon();
    ~Heart_icon()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update(Dungeon::Dungeon_shared &dungeon_shared);

private:
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float ICON_W=64.0F*Setting::SCALE,ICON_H=64.0F*Setting::SCALE,
                           ICON_X=150*Setting::SCALE+(88.0F+18.0F+20.0F)*Setting::SCALE,
                           ICON_Y=Setting::WINDOW_HEIGHT-ICON_W,
                           TIP_W=150.0F*Setting::SCALE,
                           NUM_OFFSET_X=25.0F*Setting::SCALE;
    Draw::NumberDrawer m_font;
    int current_HP=0,max_HP=0;
};
}

