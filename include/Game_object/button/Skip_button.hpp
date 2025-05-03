#pragma once

#include "RUtil/Hitbox.hpp"
#include "WindowSize.hpp"

namespace Button{
class Skip_button
{
public:
    Skip_button();
    ~Skip_button()=default;
private:
    float current_x,current_y;
    float target_x,target_y;
    bool is_hidden;
    RUtil::Hitbox hb;
    
    static constexpr float SHOW_X = (float)Setting::WINDOW_WIDTH/2.0F,
                           SHOW_Y = (float)Setting::WINDOW_HEIGHT/2.0F - 340.0F*Setting::SCALE;
    static constexpr float HB_W=260.0F*Setting::SCALE,
                           HB_H=80.0F*Setting::SCALE;
};
}