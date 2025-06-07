#include "Game_object/effect/Ghostly_fire_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect{
    static inline auto &IMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_fire1))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_fire1);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_fire2);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_fire3);
        }
    }

    Ghostly_fire_eff::Ghostly_fire_eff(float x, float y, bool is_weak)
        :weak(is_weak),
        img_type(RUtil::Random::GetRandomInt(3)),
        x(x + RUtil::Random::GetRandomFloat(-2.0F, 2.0F)*Setting::SCALE - static_cast<float>(IMG(img_type)->GetRegionWidth())/2.0F),
        y(y + RUtil::Random::GetRandomFloat(-2.0F, 2.0F)*Setting::SCALE - static_cast<float>(IMG(img_type)->GetRegionHeight())/2.0F),
        speed_x(RUtil::Random::GetRandomFloat((is_weak?-2.0F:-10.0F), (is_weak?2.0F:10.0F))*Setting::SCALE),
        speed_y(RUtil::Random::GetRandomFloat((is_weak?0.0F:20.0F), (is_weak?80.0F:150.0F))*Setting::SCALE)
    {
        duration=1.0F;
        scale=Setting::SCALE*RUtil::Random::GetRandomFloat((is_weak?2.0F:5.0F), (is_weak?3.0F:6.0F));
    }

    void Ghostly_fire_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(RUtil::ToRGBA(RUtil::Colors::CHARTREUSE), duration*0.5F);
        auto&img=IMG(img_type);
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), 0.0F, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale*(weak?1.0F:RUtil::Random::GetRandomFloat(0.95F, 1.05F)), this->scale*(weak?1.0F:RUtil::Random::GetRandomFloat(0.95F, 1.05F)));
    }

    void Ghostly_fire_eff::update(){
        x+=speed_x*DT;
        y+=speed_y*DT;
        if(!weak&&scale>0.1F) scale-=DT*0.25F;
        TimeGo();
    }
}