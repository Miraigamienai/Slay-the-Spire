#include "Game_object/effect/Camfire_burning_effect.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &GetIMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke1))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame4);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame5);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame6);
        }
    }

    void Camfire_burning_effect::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
        r2->SetColor(this->color, this->color_a);
        auto &img=GetIMG(img_type);
        r2->draw(img ,this->x, this->y, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), this->angle, (float)img->GetRegionWidth()/2.0F, (float)img->GetRegionHeight()/2.0F, this->scale, this->scale, flip_x, false);
    }

    void Camfire_burning_effect::update(){
        if(this->delay_timer>0.0F){
            delay_timer-=DT;
        }else{
            this->x+=speed_x*DT;
            this->y+=speed_y1*DT;
            this->speed_y1=RUtil::Math::varlerp(this->speed_y1, this->speed_y2, 3.0F, 0.01F);
            this->scale*=1.0F-DT/10.0F;
            if(this->start_duration-this->duration<0.75F){
                this->color_a=RUtil::Math::interpolation_fade(0.0F, target_a, (this->start_duration-this->duration)/0.75F);
            }else if(this->duration<1.0F){
                this->color_a=RUtil::Math::interpolation_fade(0.0F, target_a, this->duration/1.0F);
            }
            TimeGo();
        }
    }
    void Camfire_burning_effect::Initial(Uint32 color_rgb){
        this->is_done=false;
        using namespace RUtil;
        this->is_done=false;
        img_type =Random::GetRandomInt(3);
        this->color=color_rgb;
        this->color_a=0.0F;
        this->start_duration = this->duration = 1.75F;
        this->scale=Random::GetRandomFloat(3.0F, 4.0F);
        auto &img=GetIMG(img_type);
        this->x= Random::GetRandomFloat(1200.0F ,1770.0F) *Setting::SCALE - static_cast<float>(img->GetRegionWidth())/2.0F;
        this->y= static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F - 200.0F*Setting::SCALE - static_cast<float>(img->GetRegionHeight())/2.0F;
        this->speed_x=Random::GetRandomFloat(-70.0F, 70.0F)*Setting::SCALE;
        this->speed_y1=0.0F;
        this->speed_y2=Random::GetRandomFloat(250.0F, 450.0F)*Setting::SCALE - std::abs(this->x-1485.0F*Setting::SCALE)/2.0F;
        this->flip_x=Random::GetRandomBoolean();
        this->target_a=Random::GetRandomFloat(0.2F, 0.6F);
        this->delay_timer=Random::GetRandomFloat(0.0F, 0.1F);
        this->angle=Random::GetRandomFloat(-10.0F, 10.0F);
    } 
} // namespace Effect
