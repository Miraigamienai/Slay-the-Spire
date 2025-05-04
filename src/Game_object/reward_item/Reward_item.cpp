#include "Game_object/reward_item/Reward_item.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Game_Input.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReTexture.hpp"
#include "WindowSize.hpp"

namespace Reward{
    Reward_item::Reward_item()
        :flash_timer(0.0F),
        y(0.0F),
        hb(460.0F * Setting::SCALE, 90.0F * Setting::SCALE),
        eff_dur(EFF_DUR),
        eff_scale(Setting::SCALE),
        eff_a(0.0F){}

    void Reward_item::update(){
        //flash update
        if(this->flash_timer!=0.0F){
            this->flash_timer-=RUtil::Game_Input::delta_time();
            if(this->flash_timer<0.0F) flash_timer=0.0F;
        }
        //hb update
        this->hb.update();
        //eff update
        eff_dur-=RUtil::Game_Input::delta_time();
        if(eff_dur<0.0F){
            eff_dur=EFF_DUR;
        }
        this->eff_scale=Setting::SCALE * (1.0F+(EFF_DUR-eff_dur)/20.0F);
        this->eff_a=RUtil::Math::interpolation_fade(0.0F, 1.0F, eff_dur/EFF_DUR)/12.0F;
    }

    void Reward_item::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(taking_reward){
            this->child_render(r2);
            return;
        }

        if(this->hb.Hovered())
            r2->SetColor(HOVERED_COLOR,1.0F);
        else
            r2->SetColor(COLOR,0.8F);
        
        if(this->hb.ClickStarted())
            r2->draw(LIST_IMG, (float)Setting::WINDOW_WIDTH/2.0F-232.0F, y-49.0F, 464.0F, 98.0F, 0.0F, 232.0F, 49.0F, Setting::SCALE*0.98F, Setting::SCALE*0.98F);
        else
            r2->draw(LIST_IMG, (float)Setting::WINDOW_WIDTH/2.0F-232.0F, y-49.0F, 464.0F, 98.0F, 0.0F, 232.0F, 49.0F, Setting::SCALE, Setting::SCALE);
        
        //flash render
        if(this->flash_timer!=0.0F){
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
            r2->SetColor(0.6F,1.0F,1.0F, this->flash_timer*1.5F);
            r2->draw(LIST_IMG, (float)Setting::WINDOW_WIDTH/2.0F-232.0F, y-49.0F, 464.0F, 98.0F, 0.0F, 232.0F, 49.0F, Setting::SCALE*1.03F, Setting::SCALE*1.15F);
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        this->child_render(r2);

        if(this->hb.Hovered())
            child_render_text(r2, RUtil::GOLD_COLOR);
        else
            child_render_text(r2, RUtil::CREAM_COLOR);
        
        if(!hb.Hovered()){
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
            r2->SetColor(RUtil::WHITE, eff_a);
            r2->draw(LIST_IMG, (float)Setting::WINDOW_WIDTH/2.0F-232.0F, y-49.0F, 464.0F, 98.0F, 0.0F, 232.0F, 49.0F, Setting::SCALE, eff_scale+Setting::SCALE*0.05F);
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }

    const std::shared_ptr<Draw::ReTexture>&Reward_item::LIST_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/reward/rewardListItemPanel.png");
}