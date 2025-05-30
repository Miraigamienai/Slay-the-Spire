#include "Game_object/effect/Buff_particle_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_buffVFX1))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_buffVFX1);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_buffVFX2);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_buffVFX3);
        }
    }

    void Buff_particle_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(RUtil::WHITE, color_a);
        auto&img=IMG(img_type);
        r2->draw(img, x - static_cast<float>(img->GetRegionWidth())/2.0F, y - static_cast<float>(img->GetRegionHeight())/2.0F, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), angle, img->offsetX, img->offsetY, this->scale, this->scale);
    }

    void Buff_particle_eff::update(){
        scale+=DT*0.5F*Setting::SCALE;
        color_a=RUtil::Math::interpolation_fade(1.0F, 0.0F, 1.0F-duration/DUR);
        y+=DT*speed_y;
        TimeGo();
    }

    void Buff_particle_eff::Initial(float x, float y){
        is_done=false;
        duration=DUR;
        color_a=1.0F;
        scale=RUtil::Random::GetRandomFloat(1.0F, 1.5F)*Setting::SCALE;
        this->x=x+RUtil::Random::GetRandomFloat(-25.0F, 25.0F)*Setting::SCALE;
        this->y=y+RUtil::Random::GetRandomFloat(-20.0F, 10.0F)*Setting::SCALE;
        speed_y=RUtil::Random::GetRandomFloat(30.0F, 50.0F)*Setting::SCALE;
        angle=RUtil::Random::GetRandomFloat(-5.0F, 5.0F);
        img_type=RUtil::Random::GetRandomInt(3);
    }
} // namespace Effect
