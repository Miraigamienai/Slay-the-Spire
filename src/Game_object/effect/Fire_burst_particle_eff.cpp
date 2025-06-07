#include "Game_object/effect/Fire_burst_particle_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_fire1))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_fire1);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_fire2);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_fire3);
        }
    }
    
    Fire_burst_particle_eff::Fire_burst_particle_eff(float x, float y)
        :img_type(RUtil::Random::GetRandomInt(3)),
        x(x - static_cast<float>(IMG(img_type)->GetRegionWidth())/2.0F),
        y(y - static_cast<float>(IMG(img_type)->GetRegionHeight())/2.0F),
        speed_x(RUtil::Random::GetRandomFloat(-900.0F, 900.0F)*Setting::SCALE),
        speed_y(RUtil::Random::GetRandomFloat(0.0F, 500.0F)*Setting::SCALE),
        angle(RUtil::Random::GetRandomFloat(-10.0F, 10.0F)),
        floor(RUtil::Random::GetRandomFloat(100.0F, 250.0F)*Setting::SCALE)
    {
        scale=RUtil::Random::GetRandomFloat(2.0F, 4.0F)*Setting::SCALE;
        color_a=0.0F;
        color=RUtil::Math::GetColorUint32_RGB(
            RUtil::Random::GetRandomFloat(0.1F, 0.3F),
            RUtil::Random::GetRandomFloat(0.8F, 1.0F),
            RUtil::Random::GetRandomFloat(0.1F, 0.3F)
        );
        duration=RUtil::Random::GetRandomFloat(0.5F, 1.0F);
    }

    void Fire_burst_particle_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(color, color_a);
        auto &img=IMG(img_type);
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale, this->scale);
    }
    
    void Fire_burst_particle_eff::update(){
        speed_y+=180.0F*Setting::SCALE/scale*DT;
        x += speed_x*DT*std::sin(DT);//?
        y += speed_y*DT;
        if(scale>0.3*Setting::SCALE)
            scale-=2.0F*DT;
        if(y<floor){
            speed_y*=-0.75F;
            y=floor+0.1F;
            speed_x*=1.1F;
        }
        if(1.0F-duration<0.1F) color_a=RUtil::Math::interpolation_fade(0.0F, 1.0F, (1.0F-duration)*10.0F);
        else color_a=RUtil::Math::interpolation_powout2(0.0F, 1.0F, duration);
        TimeGo();
    }
} // namespace Effect
