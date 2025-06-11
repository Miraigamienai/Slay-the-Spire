#include "Game_object/effect/Intense_zoom_particle.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_cone8))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_cone8);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_cone5);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_cone6);
        }
    }

    using namespace RUtil;

    Intense_zoom_particle::Intense_zoom_particle(float x, float y)
        :img_type(Random::GetRandomInt(3)),
        x(x),
        y(y - static_cast<float>(IMG(img_type)->GetRegionHeight())/2.0F),
        call_randomize_timer(Random::GetRandomFloat(0.0F, 0.05F))
    {
        duration = DUR;
        randomize();
    }

    void Intense_zoom_particle::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(RUtil::GOLD_COLOR, color_a);
        auto&img=IMG(img_type);
        r2->draw(img, x+offset_x, y, static_cast<float>(img->GetRegionWidth())*length_x, static_cast<float>(img->GetRegionHeight())*length_y, angle, -offset_x, static_cast<float>(img->GetRegionHeight())/2.0F, Setting::SCALE, Setting::SCALE);  
    }

    void Intense_zoom_particle::update(){
        call_randomize_timer-=DT;
        if(call_randomize_timer<0.0F){
            call_randomize_timer=Random::GetRandomFloat(0.0F, 0.05F);
            randomize();
        }
        TimeGo();
    }

    void Intense_zoom_particle::randomize(){
        angle=Random::GetRandomFloat(0.0F, 360.0F);
        offset_x=Random::GetRandomFloat(200.0F, 600.0F)*Setting::SCALE*(2.0F-duration);
        length_x=Random::GetRandomFloat(1.0F, 1.3F);
        length_y=Random::GetRandomFloat(0.9F, 1.2F);
        color_a=Random::GetRandomFloat(0.2F, 0.7F) * Math::interpolation_powout2(0.0F, 1.0F, duration/DUR);
    }
    
} // namespace Effect
