#include "Game_object/power/Power_group.hpp"
#include "Game_object/power/Powers.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Power{
    static constexpr float ICON_PADDING = 48.0F*Setting::SCALE;

    void Power_group::render(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const{
        //icon
        float offset_x = 10.0F*Setting::SCALE;
        for(const auto&it:box){
            it->render_img(r2, x+offset_x, y-48.0F*Setting::SCALE, color_a);
            offset_x+=ICON_PADDING;
        }
        //power_effs
        power_effs.render(r2);
        //amount
        offset_x = 32.0F*Setting::SCALE;
        for(const auto&it:box){
            it->render_amount(r2, x+offset_x, y-66.0F*Setting::SCALE, color_a);
            offset_x+=ICON_PADDING;
        } 
    }
    
    void update(){

    }
}