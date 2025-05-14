#include <algorithm>

#include "Game_object/button/Cancel_button.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Game_Input.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

namespace Button{
    void Cancel_button::update(){
        if(!is_hidden){
            oscillate_timer+=RUtil::Game_Input::delta_time()*3.0F;
            this->hb.update();
        }
        //update x
        if(current_x!=target_x){
            this->current_x=RUtil::Math::varlerp(this->current_x,this->target_x,9.0F,Setting::SCALE);
            hb.move(this->current_x + HB_OFFSET_X, SHOW_Y + HB_OFFSET_Y);
        }
    }

    void Cancel_button::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::WHITE);
        r2->draw(SHADOW_BUTTON, current_x-256.0F, SHOW_Y-128.0F, 512.0F, 256.0F, 0.0F, 256.0F, 128.0F, Setting::SCALE, Setting::SCALE);
        r2->SetColor(RUtil::GOLD_COLOR, std::abs(std::cos(oscillate_timer))/2.0F + 0.3F);
        r2->draw(OUTLINE_BUTTON, current_x-256.0F, SHOW_Y-128.0F, 512.0F, 256.0F, 0.0F, 256.0F, 128.0F, Setting::SCALE, Setting::SCALE);
        r2->SetColor(RUtil::WHITE);
        r2->draw(NORMAL_BUTTON, current_x-256.0F, SHOW_Y-128.0F, 512.0F, 256.0F, 0.0F, 256.0F, 128.0F, Setting::SCALE, Setting::SCALE);
        if(this->hb.Hovered()){
            //lighter
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
            r2->SetColor(RUtil::WHITE, 0.3F);
            r2->draw(NORMAL_BUTTON, current_x-256.0F, SHOW_Y-128.0F, 512.0F, 256.0F, 0.0F, 256.0F, 128.0F, Setting::SCALE, Setting::SCALE);
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        if(this->text!=nullptr){
            this->text->SetFontSize(32);
            if(this->hb.ClickStarted()){
                text->SetFontColor(RUtil::ToRGBA(RUtil::Colors::LIGHT_GRAY));
            }else{
                text->SetFontColor(RUtil::ToRGBA(RUtil::Colors::LEMON_CHIFFON));
            }
            text->render_center(r2, this->current_x+TEXT_OFFSET_X, SHOW_Y+TEXT_OFFSET_Y, 0.0F, 0.0F, 0.0F, Setting::SCALE);
        }
    }

    const std::shared_ptr<Draw::ReTexture> &Cancel_button::NORMAL_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/cancelButton.png"),
                                           &Cancel_button::OUTLINE_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/cancelButtonOutline.png"),
                                           &Cancel_button::SHADOW_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/cancelButtonShadow.png");

}