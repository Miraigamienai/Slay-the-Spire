#include <array>

#include "Game_object/effect/Exhaust_ember_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect{
    static inline auto &GetIMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_dust1))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_dust1);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_dust2);
            case 2:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_dust3);
            case 3:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_dust4);
            case 4:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_dust5);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_dust6);
        }
    }

    using namespace RUtil;
    
    static constexpr std::array<Uint32, 3> color_convert{
        ToRGBA(Colors::CORAL),
        ToRGBA(Colors::ORANGE),
        ToRGBA(Colors::TOMATO)
    };

    Exhaust_ember_eff::Exhaust_ember_eff(float x, float y)
        :img_type(Random::GetRandomInt(6)),
        x(x + Random::GetRandomFloat(-170.0F, 170.0F)*Setting::SCALE),
        y(y + Random::GetRandomFloat(-220.0F, 150.0F)*Setting::SCALE),
        speed_x(Random::GetRandomFloat(-150.0F, 150.0F)*Setting::SCALE),
        speed_y(Random::GetRandomFloat(-100.0F, 300.0F)*Setting::SCALE),
        angle(Random::GetRandomFloat(0.0F, 360.0F)),
        angle_speed(Random::GetRandomFloat(-700.0F, 700.0F)),
        target_scale(Random::GetRandomFloat(0.4F, 0.8F)),
        start_duration(Random::GetRandomFloat(0.6F, 1.4F))
    {
        this->color = color_convert[Random::GetRandomInt(3)];
        this->color_a = 1.0F;
        start_duration *= start_duration;
        this->duration = start_duration;
        this->scale = 0.01F;
    }

    void Exhaust_ember_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        auto&img=GetIMG(img_type);
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a);
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), this->angle, img->offsetX, img->offsetY, this->scale, this->scale);
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
        r2->SetColor(color, color_a/3.0F);
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), this->angle, img->offsetX, img->offsetY, this->scale, this->scale);
    }

    void Exhaust_ember_eff::update(){
        x+=speed_x*DT;
        y+=speed_y*DT;
        angle+=angle_speed*DT;
        scale=Math::interpolation_swing(0.01F, target_scale, 1.0F-duration/start_duration);
        if(duration<0.5F) color_a=duration*2.0F;
        TimeGo();
    }
}