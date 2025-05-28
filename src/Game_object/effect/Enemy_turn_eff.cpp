#include "Game_object/effect/Enemy_turn_eff.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "Game_object/effect/Battle_start_eff.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Text_layout.hpp"

namespace Effect{
    Enemy_turn_eff::Enemy_turn_eff(Uint32 dungeon_fade_color)
        :current_h(0.0F)
    {
        this->duration=2.0F;
        auto fade_vec3=RUtil::Math::TO_VEC3(dungeon_fade_color)/2.0F;
        this->color=RUtil::Math::GetColorUint32_RGB(fade_vec3.r, fade_vec3.g, fade_vec3.b);
        this->color_a=0.0F;
        this->scale = 3.0F*Setting::SCALE;
    }
    
    void Enemy_turn_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a*0.8F);
        r2->draw(Fade_wide::white_square, 0.0F, (static_cast<float>(Setting::WINDOW_HEIGHT)-current_h)/2.0F, static_cast<float>(Setting::WINDOW_WIDTH), current_h);
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        const auto &text=RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::BattleStartEffect)[2];
        text->ChangeFontWeight(FontWeight::bold);
        text->SetFontColorAlpha(RUtil::GOLD_COLOR, color_a);
        text->SetFontSize(Battle_start_eff::FONTSIZE);
        text->render_center(r2, static_cast<float>(Setting::WINDOW_WIDTH)/2.0F, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F, 0.0F, 0.0F, 0.0F, this->scale);
    }
    
    void Enemy_turn_eff::update(){
        if(duration>1.5F){
            current_h = RUtil::Math::Apply(current_h, TARGET_H, DT*3.0F);
            scale = RUtil::Math::interpolation_exp10in(1.0F*Setting::SCALE, 3.0F*Setting::SCALE, (duration-1.5F)*2.0F);
            color_a = RUtil::Math::interpolation_exp10in(1.0F, 0.0F, (duration-1.5F)*2.0F);
        }else if(duration<0.5F){
            current_h = RUtil::Math::Apply(current_h, 0.0F, DT*3.0F);
            scale = RUtil::Math::Apply(0.9F*Setting::SCALE, 1.0F*Setting::SCALE, std::pow(duration*2.0F, 3));
            color_a = RUtil::Math::Apply(0.0F, 1.0F, std::pow(duration*2.0F, 3));
        }
        TimeGo();
    }
}