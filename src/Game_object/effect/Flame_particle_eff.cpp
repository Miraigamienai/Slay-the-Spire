#include "Game_object/effect/Flame_particle_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect{
    static inline auto &IMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame4))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame4);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame5);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame6);
        }
    }

    using namespace RUtil;

    Flame_particle_eff::Flame_particle_eff(float x, float y)
        :start_duration(Random::GetRandomFloat(0.6F, 1.5F)),
        img_type(Random::GetRandomInt(3)),
        x(x + Random::GetRandomFloat(-13.0F, 13.0F)*Random::GetRandomFloat(-13.0F, 13.0F)*Setting::SCALE - static_cast<float>(IMG(img_type)->GetRegionWidth())/2.0F),
        y(y + Random::GetRandomFloat(-180.0F, 0.0F)*Setting::SCALE - static_cast<float>(IMG(img_type)->GetRegionHeight())/2.0F),
        speed_x(Random::GetRandomFloat(-25.0F, 25.0F)*Setting::SCALE),
        speed_y(std::pow(Random::GetRandomFloat(3.0F, 30.0F), 2)/start_duration*Setting::SCALE),
        acceleration_y(Random::GetRandomFloat(-100.0F, 100.0F)*Setting::SCALE),
        scale_speed(Random::GetRandomFloat(-0.5F, 0.5F)*Setting::SCALE),
        angle(Random::GetRandomFloat(-10.0F, 10.0F)),
        flip_x(Random::GetRandomBoolean()),
        delay_time(Random::GetRandomFloat(0.0F, 0.15F))
    {
        duration=start_duration;
        const float g = Random::GetRandomFloat(0.5F, 1.0F);
        color = Math::GetColorUint32_RGB(1.0F, g, g-Random::GetRandomFloat(0.0F, 0.5F));
        scale = Random::GetRandomFloat(0.2F, 1.5F)*Setting::SCALE;
        color_a=0.0F;
    }
    
    void Flame_particle_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(color, color_a);
        auto&img=IMG(img_type);
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale, this->scale, flip_x, false);
    }
    
    void Flame_particle_eff::update(){
        if(delay_time>0.0F) delay_time-=DT;
        else{
            x+=speed_x*DT;
            y+=speed_y*DT;
            speed_y+=acceleration_y*DT;
            speed_y*=59.0F*DT;
            scale+=scale_speed*DT;
            if(duration>start_duration/2.0F) color_a=Math::interpolation_fade(0.0F, 0.5F, (start_duration-duration)/(start_duration/2.0F));
            else color_a=Math::interpolation_fade(0.0F, 0.5F, duration/(start_duration/2.0F));
        }
        TimeGo();
    }
}