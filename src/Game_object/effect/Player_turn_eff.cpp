#include "Game_object/effect/Player_turn_eff.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "Game_object/effect/Battle_start_eff.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Text_layout.hpp"

namespace Effect{
    Player_turn_eff::Player_turn_eff(Uint32 dungeon_fade_color, int turn_num)
        :current_h(0.0F),
        turn_num(std::to_string(turn_num))
    {
        this->duration=2.0F;
        auto fade_vec3=RUtil::Math::TO_VEC3(dungeon_fade_color)/2.0F;
        this->color=RUtil::Math::GetColorUint32_RGB(fade_vec3.r, fade_vec3.g, fade_vec3.b);
        this->color_a=0.0F;
        this->scale = 3.0F*Setting::SCALE;
    }
    
    void Player_turn_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        //text background
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a*0.75F);
        r2->draw(Fade_wide::white_square, 0.0F, (static_cast<float>(Setting::WINDOW_HEIGHT)-current_h)/2.0F, static_cast<float>(Setting::WINDOW_WIDTH), current_h);
        //text
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        //main text
        const auto &text=RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::BattleStartEffect)[1];
        text->ChangeFontWeight(FontWeight::bold);
        text->SetFontColorAlpha(RUtil::GOLD_COLOR, color_a);
        text->SetFontSize(Battle_start_eff::FONTSIZE);
        text->render_center(r2, static_cast<float>(Setting::WINDOW_WIDTH)/2.0F, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F + MAIN_MSG_OFFSET, 0.0F, 0.0F, 0.0F, this->scale);
        //turn text & turn number
        const auto&turn_text=RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::BattleStartEffect)[3];
        turn_text->ChangeFontWeight(FontWeight::bold);
        turn_text->SetFontColorAlpha(TURN_MSG_COLOR, color_a);
        turn_text->SetFontSize(TURN_NUM_FONT_SIZE);
        const auto num_half_width=s_turn_num_drawer.Width(turn_num)/2.0F;
        turn_text->render_center(r2, static_cast<float>(Setting::WINDOW_WIDTH)/2.0F + num_half_width, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F + TURN_MSG_OFFSET, 0.0F, -num_half_width, 0.0F, this->scale);
        r2->SetColor(TURN_MSG_COLOR, color_a);
        s_turn_num_drawer.render_center(r2, turn_num, static_cast<float>(Setting::WINDOW_WIDTH)/2.0F - turn_text->GetWidth()/2.0F, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F + TURN_MSG_OFFSET, 0.0F, turn_text->GetWidth()/2.0F, 0.0F, this->scale);    
    }
    
    void Player_turn_eff::update(){
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

    const Draw::NumberDrawer Player_turn_eff::s_turn_num_drawer{TURN_NUM_FONT_SIZE, FontWeight::bold};
}