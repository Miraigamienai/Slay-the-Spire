#include <GL/glew.h> 

#include "Game_object/effect/Card_flash.hpp"
#include "Draw/Atlas_Region.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    Card_flash::Card_flash(const std::shared_ptr<Draw::Atlas_Region>&silhouette,const float &card_x,const float &card_y,const float &card_angle,const float &card_scale,const bool quick_end):card_x(card_x),card_y(card_y),card_angle(card_angle),card_scale(card_scale),img(silhouette){
        change_color(DFAULT_COLOR);
        if(quick_end){
            this->duration=0.0F;
            this->is_done=true;
        }
    }
    void Card_flash::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
        r2->SetColor(color,this->duration);
        const float scale_factor=card_scale*(this->scale+1.0F)*Setting::SCALE;
        if(is_super_flash){
            r2->draw(IMG_FLASH, card_x + img->offsetX - (float)img->original_width/2.0F, card_y + img->offsetY - (float)img->original_height/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), card_angle, (float)img->original_width/2.0F - img->offsetX, (float)img->original_height/2.0F - img->offsetY, scale_factor*0.52F, scale_factor*0.53F);
            r2->draw(IMG_FLASH, card_x + img->offsetX - (float)img->original_width/2.0F, card_y + img->offsetY - (float)img->original_height/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), card_angle, (float)img->original_width/2.0F - img->offsetX, (float)img->original_height/2.0F - img->offsetY, scale_factor*0.55F, scale_factor*0.57F);
            r2->draw(IMG_FLASH, card_x + img->offsetX - (float)img->original_width/2.0F, card_y + img->offsetY - (float)img->original_height/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), card_angle, (float)img->original_width/2.0F - img->offsetX, (float)img->original_height/2.0F - img->offsetY, scale_factor*0.58F, scale_factor*0.6F);
        }else{
            r2->draw(img, card_x + img->offsetX - (float)img->original_width/2.0F, card_y + img->offsetY - (float)img->original_height/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), card_angle, (float)img->original_width/2.0F - img->offsetX, (float)img->original_height/2.0F - img->offsetY, scale_factor*0.52F, scale_factor*0.52F);
            r2->draw(img, card_x + img->offsetX - (float)img->original_width/2.0F, card_y + img->offsetY - (float)img->original_height/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), card_angle, (float)img->original_width/2.0F - img->offsetX, (float)img->original_height/2.0F - img->offsetY, scale_factor*0.55F, scale_factor*0.55F);
            r2->draw(img, card_x + img->offsetX - (float)img->original_width/2.0F, card_y + img->offsetY - (float)img->original_height/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), card_angle, (float)img->original_width/2.0F - img->offsetX, (float)img->original_height/2.0F - img->offsetY, scale_factor*0.58F, scale_factor*0.58F);    
        }
    }
    void Card_flash::update(){
        this->TimeGo();
        if(!is_done){
            this->scale=RUtil::Math::Apply(1.2F,1.1F,RUtil::Math::BounceIn(this->duration*2.0F));
        }
    }
    const std::shared_ptr<Draw::Atlas_Region>&Card_flash::IMG_FLASH=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_512_card_flash_vfx);
}