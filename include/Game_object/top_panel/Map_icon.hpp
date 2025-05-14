#pragma once

#include <memory>
#include "Game_object/top_panel/Basic_panel.hpp"
#include "WindowSize.hpp"

namespace TopPanel
{
class Map_icon final :public Basic_panel
{

public:
    Map_icon();
    ~Map_icon()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update(Dungeon::Dungeon_shared &dungeon_shared) override;

private:
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float ICON_W=64.0F*Setting::SCALE,ICON_H=64.0F*Setting::SCALE,
                           ICON_X=Setting::WINDOW_WIDTH - (ICON_W + 10.0F*Setting::SCALE) * 3.0F,
                           ICON_Y=Setting::WINDOW_HEIGHT-ICON_W;
};
}

