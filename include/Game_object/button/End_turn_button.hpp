#pragma once

#include <memory>

#include "Game_object/button/Buttons.hpp"
#include "Game_object/effect/Effect_group.hpp"//glow_list
#include "RUtil/Some_Math.hpp"//RGB
#include "WindowSize.hpp"//Setting::SCALE

//fwd decl
namespace Card{
    class Card_group_handler;
}
namespace Draw{
    class ReTexture;
}

namespace Button{
class End_turn_button final:public Buttons
{
public:
    End_turn_button();
    ~End_turn_button()override=default;
    void update(const Card::Card_group_handler &card_group_handler);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void enable()noexcept{this->is_enabled=true;}//start turn
    void disable()noexcept{this->is_enabled=false;}//end turn
    void show()noexcept{
        if(is_hidden){
            is_hidden=false;
            target_x=SHOW_X;
            glow_timer=0.0F;
        }
    }
    void hide()noexcept{
        if(!is_hidden){
            is_hidden=true;
            target_x=HIDE_X;
        }
    }
private:
    float current_x,current_y,target_x;//only move x
    bool is_hidden,is_glowing;
    //is_enabled: Controlled externally.
    //is_disabled: Controlled internally.
    bool is_enabled,is_disabled;
    float glow_timer;
    Effect::Effect_group glow_list;
    static constexpr float SHOW_X = 1640.0F * Setting::SCALE,
                           SHOW_Y = 210.0F * Setting::SCALE;
    static constexpr float HIDE_X = SHOW_X + 500.0F * Setting::SCALE;
    static constexpr auto DISABLED_COLOR = RUtil::Math::GetColorUint32_RGB(0.7F, 0.7F, 0.7F);
    static const std::shared_ptr<Draw::ReTexture> &NORMAL_BUTTON,&GLOW_BUTTON,&HOVER_BUTTON;
};
}