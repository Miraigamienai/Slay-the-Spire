#include "Game_object/effect/Rest_option_black_screen.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    Rest_option_black_screen::Rest_option_black_screen(Uint32 dungeon_fade_color){
        this->duration = 3.0F;
        this->scale=this->duration;////NOTE:'scale' is used to be start_duration here. 
        this->color=dungeon_fade_color;
        this->color_a=0.0F;
    }

    void Rest_option_black_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(color, color_a);
        r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT));
    }

    void Rest_option_black_screen::update(){
        if(duration+0.5F>scale){
            this->color_a=RUtil::Math::interpolation_fade(1.0F, 0.0F, (duration+0.5F-scale)*2.0F);
        }else if(duration<1.0F){
            this->color_a=RUtil::Math::interpolation_fade(0.0F, 1.0F, duration);
        }
    }
} // namespace Effect
