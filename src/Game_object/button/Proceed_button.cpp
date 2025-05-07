#include "Game_object/button/Proceed_button.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

namespace Button
{
    static inline auto DT()noexcept(noexcept(RUtil::Game_Input::delta_time())){
        return RUtil::Game_Input::delta_time();
    }

    Proceed_button::Proceed_button()
        :hb(HB_W,HB_H),
        current_x(HIDE_X),
        target_x(HIDE_X),
        is_hidden(true),
        should_flash(false),
        m_scale(Setting::SCALE),
        oscillate_timer(0.0F),
        text(nullptr)
    {

    }

    void Proceed_button::update(){
        if(!is_hidden){
            this->oscillate_timer+=DT();
            this->m_scale=Setting::SCALE*1.1F + std::cos(this->oscillate_timer)/50.0F;
            if(this->current_x-SHOW_X < CLICKABLE_DISTANT)
                this->hb.update();
            else
                this->hb.ResetAll();

            should_flash=hb.JustHovered();            
        }
        //move x
        if(current_x!=target_x){
            this->current_x=RUtil::Math::varlerp(this->current_x,this->target_x,9.0F,Setting::SCALE);
            hb.move(this->current_x,SHOW_Y);
        }
    }

    void Proceed_button::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        //shadow
        r2->SetColor(RUtil::WHITE);
        r2->draw(SHADOW_BUTTON, this->current_x-256.0F, SHOW_Y-256.0F, 512.0F, 512.0F, 0.0F, 256.0F, 256.0F, this->m_scale, this->m_scale);
        //outline
        r2->SetColor(1.0F, 0.9F, 0.2F, std::cos(oscillate_timer)/5.0F +0.6F);
        r2->draw(OUTLINE_BUTTON, this->current_x-256.0F, SHOW_Y-256.0F, 512.0F, 512.0F, 0.0F, 256.0F, 256.0F, this->m_scale, this->m_scale);
        //button
        r2->SetColor(RUtil::WHITE);
        r2->draw(NORMAL_BUTTON, this->current_x-256.0F, SHOW_Y-256.0F, 512.0F, 512.0F, 0.0F, 256.0F, 256.0F, this->m_scale, this->m_scale);
        
        if(this->hb.Hovered()){
            //lighter
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
            r2->SetColor(RUtil::WHITE,0.3F);
            r2->draw(NORMAL_BUTTON, this->current_x-256.0F, SHOW_Y-256.0F, 512.0F, 512.0F, 0.0F, 256.0F, 256.0F, this->m_scale, this->m_scale);
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        if(this->text!=nullptr){
            this->text->SetFontSize(32);
            if(hb.Hovered()&&!hb.ClickStarted()){
                this->text->SetFontColor(RUtil::CREAM_COLOR);
            }else if(hb.ClickStarted()){
                this->text->SetFontColor(RUtil::ToRGBA(RUtil::Colors::LIGHT_GRAY));
            }else{
                this->text->SetFontColor(RUtil::ToRGBA(RUtil::Colors::LEMON_CHIFFON));
            }
            this->text->render_center(r2, this->current_x, SHOW_Y, 0.0F ,0.0F, 0.0F, Setting::SCALE);
        }
    }
    
    const std::shared_ptr<Draw::ReTexture> &Proceed_button::NORMAL_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/proceedButton.png"),
                                           &Proceed_button::OUTLINE_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/proceedButtonOutline.png"),
                                           &Proceed_button::SHADOW_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/proceedButtonShadow.png");

} // namespace Button
