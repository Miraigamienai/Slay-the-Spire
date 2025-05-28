#include <string>

#include "Game_object/effect/Power_buff_debuff_eff.hpp"
#include "RUtil/Powers_Text_Reader.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Text_layout.hpp"
#include "Draw/Draw_2D.hpp"

namespace Effect{
    void Power_buff_debuff_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        auto &text=RUtil::Powers_Text_Reader::GetName(power_id);
        text->ChangeFontWeight(FontWeight::bold);
        text->SetFontSize(FONT_SIZE);
        text->SetFontAlpha(this->color_a);
        text->SetFontColor(this->color);
        if(with_number){
            std::string msg="+" + std::to_string(number) + " ";
            //w=4 mid=2
            //w=1,3 mid=0.5,2.5 = mid-3/2,mid+1/2
            r2->SetColor(this->color, this->color_a);
            s_number_drawer.render_center(r2, msg, this->x - text->GetWidth()/2.0F, this->y + this->offset_y, 0.0F, text->GetWidth()/2.0F, 0.0F, Setting::SCALE*1.25F);
            const auto num_half_width=s_number_drawer.Width(msg)/2.0F;
            text->render_center(r2, this->x + num_half_width, this->y + this->offset_y, 0.0F, -num_half_width, 0.0F, Setting::SCALE*1.25F);
        }else{
            text->render_center(r2, this->x, this->y + this->offset_y, 0.0F, 0.0F, 0.0F, Setting::SCALE*1.25F);
        }
    }

    void Power_buff_debuff_eff::update()
    {
        this->current_rgb=RUtil::Math::Apply(current_rgb, target_rgb, std::pow(duration/DUR, 2));
        this->color=RUtil::Math::GetColorUint32_RGB(current_rgb.r, current_rgb.g, current_rgb.b);
        this->color_a=RUtil::Math::interpolation_exp10out(0.0F, 1.0F, duration/DUR);
        this->offset_y=RUtil::Math::interpolation_exp10in(TARGET_OFFSET_Y, START_OFFSET_Y, duration/DUR);
        TimeGo();
    }

    const Draw::NumberDrawer Power_buff_debuff_eff::s_number_drawer(FONT_SIZE, FontWeight::bold);
}