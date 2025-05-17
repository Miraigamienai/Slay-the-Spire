#include "Game_object/power/Power_group.hpp"
#include "Draw/Text_layout.hpp"
#include "Draw/Draw_2D.hpp"

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

    void Power_group::render_tip(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y)const{
        bool is_left = x > static_cast<float>(Setting::WINDOW_WIDTH)/2.0F;
        const float now_y = y - calculate_tip_height()/2.0F;
        float now_x = x;
        float curr_h=0.0F;
        for(const auto&it:box){
            const float desc_h = it->GetDesc()->GetHeight() + TIP_PADDING_Y;
            if(curr_h + desc_h >= TIP_MAX_HEIGHT){
                curr_h=0.0F;
                if(is_left) now_x-=324.0F*Setting::SCALE;
                else now_x+=324.0F*Setting::SCALE;
            }
            it->render_tip(r2, now_x, now_y-curr_h);
            curr_h+=desc_h;
        }
    }
    
    float Power_group::calculate_tip_height()const{
        float max_h=0.0F;
        float curr_h=0.0F;
        for(const auto&it:box){
            const float desc_h = it->GetDesc()->GetHeight() + TIP_PADDING_Y;
            if(curr_h + desc_h > TIP_MAX_HEIGHT){
                if(curr_h>max_h) max_h=curr_h;
                curr_h=desc_h;
            }else{
                curr_h+=desc_h;
            }
        }
        return curr_h>max_h ? curr_h : max_h;
    }

    void at_turn_end(){

    }
}