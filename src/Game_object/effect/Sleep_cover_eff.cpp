#include "Game_object/effect/Sleep_cover_eff.hpp"
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
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke1);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke2);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke3);
        }
    }

    void Sleep_cover_eff::Initial()noexcept{
        using namespace RUtil;
        this->is_done=false;
        this->duration = this->start_duration = Random::GetRandomFloat(2.0F, 2.5F);
        this->scale=Random::GetRandomFloat(16.0F,30.0F)*Setting::SCALE;
        const float color_base=Random::GetRandomFloat(0.5F, 0.7F);
        this->color=Math::GetColorUint32_RGB(color_base, color_base-0.03F, color_base-0.07F);
        this->color_a=0.0F;
        this->img_type =Random::GetRandomInt(3);
        auto &img=GetIMG(img_type);
        this->x=Random::GetRandomFloat(-100.0F*Setting::SCALE, static_cast<float>(Setting::WINDOW_WIDTH)+100.0F*Setting::SCALE) - static_cast<float>(img->GetRegionWidth())/2.0F;
        this->y=Random::GetRandomFloat(-100.0F*Setting::SCALE, static_cast<float>(Setting::WINDOW_HEIGHT)+100.0F*Setting::SCALE) - static_cast<float>(img->GetRegionHeight())/2.0F;
        this->angel=Random::GetRandomFloat(0.0F,360.0F);
        this->angel_speed=Random::GetRandomFloat(-30.0F,30.0F);
        this->target_a=Random::GetRandomFloat(0.4F,0.7F);
        this->flip_x=Random::GetRandomBoolean();
        this->flip_y=Random::GetRandomBoolean();
    }   

    void Sleep_cover_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(this->color,this->color_a);
        auto &img=GetIMG(img_type);
        r2->draw(img, this->x, this->y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), this->angel, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale, this->scale, this->flip_x, this->flip_y);
    }

    void Sleep_cover_eff::update(){
        this->angel+=this->angel_speed*DT;
        if(start_duration-duration<1.0F){
            color_a=RUtil::Math::interpolation_fade(0.0F, target_a, start_duration-duration);
        }else if(duration<1.0F){
            color_a=RUtil::Math::interpolation_fade(target_a, 0.0F, 1.0F-duration);
        }
        TimeGo();
    }
    
} // namespace Effect
