#include "Game_object/effect/Exhaust_blur_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &GetIMG(bool img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_exhaust_bigBlur))){
        return img_type ? RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_exhaust_bigBlur) : RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_exhaust_smallBlur);
    }

    using namespace RUtil;
    Exhaust_blur_eff::Exhaust_blur_eff(float x, float y)
        :img_type(Random::GetRandomBoolean()),
        x(x + Random::GetRandomFloat(-150.0F, 150.0F)*Setting::SCALE - static_cast<float>(GetIMG(img_type)->GetRegionWidth())/2.0F),
        y(y + Random::GetRandomFloat(-240.0F, 150.0F)*Setting::SCALE - static_cast<float>(GetIMG(img_type)->GetRegionHeight())/2.0F),
        speed_y(Random::GetRandomFloat(60.0F, 300.0F)*Setting::SCALE),
        angle(Random::GetRandomFloat(0.0F, 360.0F)),
        angle_speed(Random::GetRandomFloat(-250.0F, 250.0F)),
        target_scale(img_type ? Random::GetRandomFloat(0.5F, 1.3F) : Random::GetRandomFloat(0.3F, 1.0F)),
        start_duration(img_type ? Random::GetRandomFloat(0.9F, 1.2F) : Random::GetRandomFloat(0.6F, 1.4F))
    {
        this->duration = start_duration;
        this->scale = 0.01F;
        const float r = Random::GetRandomFloat(0.1F, 0.4F);
        this->color = RUtil::Math::GetColorUint32_RGB(r, r, r+0.05F);
        this->color_a = 1.0F;
    }

    
    void Exhaust_blur_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a);
        auto&img=GetIMG(img_type);
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale, this->scale);
    }
    
    void Exhaust_blur_eff::update(){
        x+=Random::GetRandomFloat(-2.0F*Setting::SCALE, 2.0F*Setting::SCALE);
        y+=Random::GetRandomFloat(-2.0F*Setting::SCALE, 2.0F*Setting::SCALE) + speed_y*DT;
        angle+=angle_speed*DT;
        scale=Math::interpolation_swing(0.01F, target_scale, 1.0F-duration/start_duration);
        if(duration<0.333F) color_a=duration*3.0F;
        TimeGo();
    }
} // namespace Effect
