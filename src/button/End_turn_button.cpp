#include <GL/glew.h>//blend func

#include "Game_object/button/End_turn_button.hpp"//the hpp
#include "Game_object/effect/End_turn_button_glow.hpp"//button glwo
#include "Game_object/effect/Effect_pool.hpp"//button glow reuse
#include "Game_object/card/Card_group_handler.hpp"//dragging card check and card glow
#include "RUtil/Game_Input.hpp"//delta time
#include "RUtil/ColorValuesOnly.hpp"//colors
#include "RUtil/Image_book.hpp"//for loading img
#include "Draw/ReTexture.hpp"//button img
#include "Draw/Draw_2D.hpp"//for rendering
#include "Programs.hpp"//grayscale

namespace Button
{
    End_turn_button::End_turn_button():Buttons(0.0F,0.0F,230.0F*Setting::SCALE,110.0F*Setting::SCALE){
        this->current_x=HIDE_X;
        this->target_x=HIDE_X;
        this->current_y=SHOW_Y;
        this->is_hidden=true;
        this->is_glowing=false;
        this->is_enabled=false;
        this->is_disabled=true;
        this->glow_timer=0.0F;
    }
    void End_turn_button::update(const Card::Card_group_handler &card_group_handler){
        this->is_glowing=!card_group_handler.is_someone_canuse();
        //glow update
        if(is_glowing&&!is_hidden){
            glow_timer-=RUtil::Game_Input::delta_time();
            if(glow_timer<0.0F){
                glow_timer=1.2F;
                glow_list.AddTop(Effect::Effect_pool<Effect::End_turn_button_glow>::GetEffect(this->current_x,this->current_y));
            }
        }
        glow_list.update();
        
        //lerp
        if(this->current_x!=this->target_x)
            this->current_x=RUtil::Math::varlerp(this->current_x,this->target_x,9.0F,Setting::SCALE);
        
        if(this->is_enabled){//is_enabled takes priority over is_disabled
            this->is_disabled=this->is_hidden||card_group_handler.is_dragging();
            if(!this->is_disabled){
                this->hb.move(current_x,current_y);
                this->hb.update();
                if(this->hb.JustHovered())
                    card_group_handler.super_flash();
            }
        }
    }
    void End_turn_button::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        //here is font color
        // if(!is_enabled){
        //     //敵のターン
            
        // }else if(is_disabled){
        //     //自分のターンだが、カードをドラッグ中または使用中。
            
        // }else{
        //     //自分のターン(操作可能)
        //     if(hb.Hovered()){
        //         if(is_glowing){
        //             //no card can use
        //         }else{
        //             //there are card can use
        //         }
        //     }else if(is_glowing){
        //         //no card can use and not hoverd
        //     }else{

        //     }
        // }
        // if(!this->is_hidden){
        //     if(this->hb.ClickStarted())
        //     else if
        // }
            
        if(!is_enabled)
            r2->SwitchProgram(Programs::GrayScaleProgram());
        else if(is_disabled)
            r2->SetColor(DISABLED_COLOR,1.0F);
        else
            r2->SetColor(RUtil::Colors::WHITE);
        
        const float adj_y = (!is_hidden && hb.ClickStarted() ? -2.0F * Setting::SCALE
                           : !is_hidden && hb.Hovered()      ?  2.0F * Setting::SCALE
                           : 0.0F)+current_y;
        const auto&img=is_glowing&&!hb.ClickStarted()?GLOW_BUTTON:NORMAL_BUTTON;
        if(hb.Hovered()&&!is_disabled)
            r2->draw(HOVER_BUTTON, this->current_x-128.0F, adj_y-128.0F, 256.0F, 256.0F, 0.0F, 128.0F, 128.0F, Setting::SCALE, Setting::SCALE);
        r2->draw(img, this->current_x-128.0F, adj_y-128.0F, 256.0F, 256.0F, 0.0F, 128.0F, 128.0F, Setting::SCALE, Setting::SCALE);
        
        if(!is_enabled)
            r2->SwitchProgram(Programs::DefaultProgram());

        glow_list.render(r2);
        if(hb.Hovered()&&!is_disabled){
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
            r2->SetColor(RUtil::Colors::WHITE,0.5F);
            r2->draw(img, this->current_x-128.0F, adj_y-128.0F, 256.0F, 256.0F, 0.0F, 128.0F, 128.0F, Setting::SCALE, Setting::SCALE);
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }

    const std::shared_ptr<Draw::ReTexture> &End_turn_button::NORMAL_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/endTurnButton.png"),
                                           &End_turn_button::GLOW_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/endTurnButtonGlow.png"),
                                           &End_turn_button::HOVER_BUTTON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/endTurnHover.png");
} // namespace Button
