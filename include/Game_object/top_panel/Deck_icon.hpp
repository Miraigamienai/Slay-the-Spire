#pragma once

#include <memory>
#include "Game_object/top_panel/Basic_panel.hpp"
#include "Draw/NumberDrawer.hpp"
#include "WindowSize.hpp"

namespace TopPanel
{
class Deck_icon final :public Basic_panel
{

public:
    Deck_icon();
    ~Deck_icon()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update(Dungeon::Dungeon_shared &dungeon_shared);

private:
    int deck_num=0;
    Draw::NumberDrawer m_font;
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float ICON_W=64.0F*Setting::SCALE,ICON_H=64.0F*Setting::SCALE,
                           ICON_X=Setting::WINDOW_WIDTH-(ICON_W + 10.0F*Setting::SCALE) * 2.0F,
                           ICON_Y=Setting::WINDOW_HEIGHT-ICON_W;
};
}

