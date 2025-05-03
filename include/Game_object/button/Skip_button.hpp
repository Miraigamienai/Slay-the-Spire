#pragma once

#include <SDL_stdinc.h>
#include <memory>
#include <vector>

#include "RUtil/Hitbox.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
    class ReTexture;
    class Text_layout;
}

namespace Button{
class Skip_button
{
public:
    Skip_button();
    ~Skip_button()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void show()noexcept{
        is_hidden=false;
        this->color_a=0.0F;
        this->current_x=this->target_x=SHOW_X;
        this->hb.move(SHOW_X,SHOW_Y);
    }
    void hide(){
        is_hidden=true;
    }
    bool is_logically_clicked()const noexcept{
        return !is_hidden&&hb.Clicked();
    }
private:
    float current_x,target_x;
    float color_a;
    bool is_hidden;
    RUtil::Hitbox hb;

    static const std::vector<std::shared_ptr<Draw::Text_layout>> &text_vec;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr float SHOW_X = (float)Setting::WINDOW_WIDTH/2.0F,
                           SHOW_Y = (float)Setting::WINDOW_HEIGHT/2.0F - 340.0F*Setting::SCALE;
    static constexpr float HB_W=260.0F*Setting::SCALE,
                           HB_H=80.0F*Setting::SCALE;
};
}