#include "Game_object/dungeon/Overlay.hpp"
#include "Game_object/effect/Fade_wide.hpp"//white square
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Game_Input.hpp"

namespace Dungeon{
    void Overlay::update(){
        energy_panel.update();
        update_black_screen_a();
    }
    void Overlay::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        energy_panel.render(r2);
    }
    void Overlay::hide_combat_panel(){
        energy_panel.hide();
    }
    void Overlay::show_combat_panel(){
        energy_panel.show();
    }
    void Overlay::render_black_screen(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::BLACK, black_screen_a);
        r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT));
    }
    void Overlay::update_black_screen_a(){
        if(black_screen_target_a != black_screen_a){
            if(this->black_screen_target_a > this->black_screen_a){
                black_screen_a+=2.0F*RUtil::Game_Input::delta_time();
                if(black_screen_a>black_screen_target_a) black_screen_a=black_screen_target_a;
            }else{
                black_screen_a-=2.0F*RUtil::Game_Input::delta_time();
                if(black_screen_a<black_screen_target_a) black_screen_a=black_screen_target_a;
            }
        }
    }
}