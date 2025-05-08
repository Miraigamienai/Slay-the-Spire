#include "Game_object/room/rest_room_options/Options.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "Programs.hpp"

namespace Room{
namespace Option{
    
    Options::Options(const std::shared_ptr<Draw::ReTexture> &img, bool is_activating)
        :hb(216.0F * Setting::SCALE, 140.0F * Setting::SCALE),
        scale(NORMAL_SCALE),
        is_activating(is_activating),
        is_done(true),//default true
        is_cancelled(true),//default true
        img(img)
    {

    }
    
    void Options::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::BLACK, 0.2F);
        r2->draw(img, hb.CenterX()-128.0F+SHADOW_X, hb.CenterY()-128.0F+SHADOW_Y, 256.0F, 256.0F, 0.0F, 128.0F, 128.0F, this->scale, this->scale);
        float scale_color_a=(this->scale-NORMAL_SCALE)*10.0F/Setting::SCALE;
        r2->SetColor(1.0F, 0.93F, 0.45F, scale_color_a);
        r2->draw(OUTLINE, hb.CenterX()-128.0F, hb.CenterY()-128.0F, 256.0F, 256.0F, 0.0F, 128.0F, 128.0F, this->scale*1.075F, this->scale*1.075F);
        r2->SetColor(RUtil::WHITE);
        
        if(!is_activating)
            r2->SwitchProgram(Programs::GrayScaleProgram());
        
        r2->draw(img, hb.CenterX()-128.0F, hb.CenterY()-128.0F, 256.0F, 256.0F, 0.0F, 128.0F, 128.0F, this->scale, this->scale);
        
        if(!is_activating)
            r2->SwitchProgram(Programs::DefaultProgram());

        if(!is_activating)
            chile_label_render(r2,RUtil::ToRGBA(RUtil::Colors::LIGHT_GRAY));
        else
            chile_label_render(r2,RUtil::GOLD_COLOR);
        
        if(scale_color_a>0.001F)
            chile_description_render(r2,scale_color_a);
    }

    void Options::update(){
        this->hb.update();
        if(is_activating){
            if(!hb.ClickStarted()){
                this->scale=RUtil::Math::varlerp(this->scale, HOVER_SCALE, 8.0F, 0.003F);
                this->scale=RUtil::Math::varlerp(this->scale, HOVER_SCALE, 8.0F, 0.003F);
            }else{
                this->scale=RUtil::Math::varlerp(this->scale, NORMAL_SCALE, 8.0F, 0.003F);
            }
        }else{
            this->scale=RUtil::Math::varlerp(this->scale, NORMAL_SCALE, 8.0F, 0.003F);
        }

    }

    const std::shared_ptr<Draw::ReTexture> &Options::OUTLINE=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/options/outline.png");

}
}    