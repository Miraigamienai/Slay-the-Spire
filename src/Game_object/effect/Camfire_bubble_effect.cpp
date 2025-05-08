#include "Game_object/effect/Camfire_bubble_effect.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    
    static inline auto &GetIMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke1))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke1);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke2);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke3);
        }
    }

    void Camfire_bubble_effect::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(this->color, this->color_a);
        auto &img=GetIMG(img_type);
        r2->draw(img, this->x, this->y + out_offset_y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), this->angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale, this->scale, flip_x, flip_y);
    }
    void Camfire_bubble_effect::update(){
        this->angle+=this->angle_speed*DT;
        if(this->start_duration-this->duration<3.0F){
            this->color_a=RUtil::Math::interpolation_fade(0.0F, 0.5F, (this->start_duration-this->duration)/3.0F);
        }else if(this->duration<3.0F){
            this->color_a=RUtil::Math::interpolation_fade(0.5F, 0.0F, 1.0F-this->duration/3.0F);
        }
        TimeGo();
    }
    Camfire_bubble_effect::Camfire_bubble_effect(float x,float y,bool large,const float &offset_y)
        :img_type(RUtil::Random::GetRandomInt(3)),
        angle_speed(RUtil::Random::GetRandomFloat(-30.0F,30.0F)),
        angle(RUtil::Random::GetRandomFloat(0.0F, 360.0F)),
        flip_x(RUtil::Random::GetRandomBoolean()),
        flip_y(RUtil::Random::GetRandomBoolean()),
        out_offset_y(offset_y)
    {
        this->duration = this->start_duration = RUtil::Random::GetRandomFloat(10.0F, 20.0F);
        auto &img=GetIMG(img_type);
        this->x=RUtil::Random::GetRandomFloat(-300.0F, 300.0F)*Setting::SCALE - static_cast<float>(img->GetRegionWidth())/2.0F + x;
        this->y=RUtil::Random::GetRandomFloat(large?-200.0F:0.0F, 230.0F)*Setting::SCALE - static_cast<float>(img->GetRegionHeight())/2.0F + y;
        const float color_base=RUtil::Random::GetRandomFloat(0.8F,1.0F);
        this->color=RUtil::Math::GetColorUint32_RGB(color_base, color_base-0.03F, color_base-0.07F);
        this->color_a=0.0F;
        this->scale=RUtil::Random::GetRandomFloat(6.0F,9.0F)*Setting::SCALE;   
    }
} // namespace Effect
