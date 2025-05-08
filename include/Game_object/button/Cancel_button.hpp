#pragma once

#include <memory>

#include "RUtil/Hitbox.hpp"
#include "Draw/Text_layout.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
    class ReTexture;
}

namespace Button{
class Cancel_button
{
public:
    Cancel_button();
    ~Cancel_button()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void hide(bool immediate=false)noexcept{
        is_hidden=true;
        this->target_x=HIDE_X;
        if(immediate) this->current_x=HIDE_X;
    }
    void show()noexcept{
        is_hidden=false;
        this->target_x=SHOW_X;
    }
    void set_text(const std::shared_ptr<Draw::Text_layout> &text)noexcept{this->text=text;}
    bool is_logically_clicked()const noexcept{
        return !is_hidden&&hb.Clicked();
    }
private:
    RUtil::Hitbox hb;
    float current_x,target_x;
    bool is_hidden;
    std::shared_ptr<Draw::Text_layout> text;
    float oscillate_timer;

    static const std::shared_ptr<Draw::ReTexture> &NORMAL_BUTTON,&OUTLINE_BUTTON,&SHADOW_BUTTON;
    static constexpr float SHOW_X = 256.0F * Setting::SCALE,
                           SHOW_Y = 128.0F * Setting::SCALE;
    static constexpr float HIDE_X = SHOW_X - 400.0F * Setting::SCALE; 
    static constexpr float HB_W = 300.0F*Setting::SCALE, HB_H =100.0F*Setting::SCALE;
    static constexpr float TEXT_OFFSET_X = -136.0F * Setting::SCALE,
                           TEXT_OFFSET_Y = 57.0F * Setting::SCALE;
    static constexpr float HB_OFFSET_X = -106.0F * Setting::SCALE,
                           HB_OFFSET_Y = 60.0F * Setting::SCALE;
};
}