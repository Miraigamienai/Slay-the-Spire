#include <GL/glew.h>

#include "Game_object/button/Skip_button.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Text_layout.hpp"

namespace Button
{
    Skip_button::Skip_button()
        :current_x(SHOW_X),
        target_x(SHOW_X),
        color_a(1.0F),
        is_hidden(true),
        hb(HB_W,HB_H,SHOW_X,SHOW_Y,true){}
    
    void Skip_button::update(){
        if(!is_hidden){
            this->hb.update();
            if(this->current_x!=this->target_x){
                this->current_x=RUtil::Math::varlerp(this->current_x,this->target_x,9.0F,Setting::SCALE);
                hb.move(this->current_x,SHOW_Y);
            }
        }
        this->color_a=RUtil::Math::fadelerp(this->color_a,1.0F);
    }

    void Skip_button::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(!is_hidden){
            // 先渲染背景
            r2->SetColor(RUtil::WHITE,this->color_a);
            r2->draw(IMG, this->current_x-256.0F, SHOW_Y-128.0f, 512.0F, 256.0F, 0.0F, 256.0F, 128.0F, Setting::SCALE, Setting::SCALE);
            
            // 渲染文字（以End_turn_button的風格）
            const auto &text = text_vec[0]; // 使用"略過"文字
            text->ChangeFontWeight(FontWeight::bold);
            text->SetFontSize(35);
            text->SetFontColorAlpha(RUtil::WHITE, 1.0F);
            text->render_center(r2, this->current_x, SHOW_Y, 0.0F, 0.0F, 0.0F, 0.8F * Setting::SCALE);
            
            // 原有的點擊效果保持不變
            if(this->hb.ClickStarted()){
                r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
                r2->SetColor(RUtil::WHITE,0.3F);
                r2->draw(IMG, this->current_x-256.0F, SHOW_Y-128.0f, 512.0F, 256.0F, 0.0F, 256.0F, 128.0F, Setting::SCALE, Setting::SCALE);
                r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
        }
    }
    const std::vector<std::shared_ptr<Draw::Text_layout>> &Skip_button::text_vec=RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::CardRewardScreen);
    const std::shared_ptr<Draw::ReTexture>&Skip_button::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/reward/takeAll.png");
} // namespace Button