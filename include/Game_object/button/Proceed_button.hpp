#pragma once

#include <memory>

#include "RUtil/Hitbox.hpp"
#include "Draw/Text_layout.hpp"//for inline
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
    class ReTexture;
}

namespace Button{
class Proceed_button
{
public:
    Proceed_button();
    ~Proceed_button()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void hide()noexcept{
        is_hidden=true;
        this->target_x=HIDE_X;
    }
    void set_text(const std::shared_ptr<Draw::Text_layout> &text)noexcept{this->text=text;}
    void show()noexcept{
        is_hidden=false;
        this->target_x=SHOW_X;
    }
    bool is_logically_clicked()const noexcept{
        return !is_hidden&&hb.Clicked();
    }
    bool is_logically_just_hovered()const noexcept{return !is_hidden&&hb.JustHovered();}
private:
    RUtil::Hitbox hb;
    float current_x,target_x;
    bool is_hidden;
    float m_scale,oscillate_timer;
    std::shared_ptr<Draw::Text_layout> text;

    static const std::shared_ptr<Draw::ReTexture> &NORMAL_BUTTON,&OUTLINE_BUTTON,&SHADOW_BUTTON;
    static constexpr float SHOW_X = 1670.0F * Setting::SCALE,
                           SHOW_Y = 320.0F * Setting::SCALE;
    static constexpr float HIDE_X = SHOW_X + 500.0F * Setting::SCALE; 
    static constexpr float HB_W = 280.0F*Setting::SCALE, HB_H =156.0F*Setting::SCALE;
    static constexpr float CLICKABLE_DISTANT=20.0F*Setting::SCALE;
    
};
}