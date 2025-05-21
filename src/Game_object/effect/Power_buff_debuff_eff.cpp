#include <string>

#include "Game_object/effect/Power_buff_debuff_eff.hpp"
#include "RUtil/Powers_Text_Reader.hpp"
#include "RUtil/ColorValuesOnly.hpp"
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
            const float number_widht=s_number_drawer.Width(msg);
            const float text_width=text->GetWidth();
            const float half_width=(number_widht + text_width)/2.0F;
            r2->SetColor(this->color, this->color_a);
            s_number_drawer.render_center(r2, msg, this->x - half_width + number_widht/2.0F, this->y + this->offset_y, Setting::SCALE*1.25F);
            text->render_center(r2, this->x + half_width - text_width/2.0F, this->y + this->offset_y, 0.0F, 0.0F, 0.0F, Setting::SCALE*1.25F);
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

    Draw::NumberDrawer Power_buff_debuff_eff::s_number_drawer(FONT_SIZE, FontWeight::bold);
}