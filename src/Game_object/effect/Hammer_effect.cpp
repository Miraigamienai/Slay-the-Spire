#include "Game_object/effect/Hammer_effect.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Random.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_hammerImprint))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_hammerImprint);
    }

    Hammer_effect::Hammer_effect(float x,float y){
        using namespace RUtil;
        this->color_a=0.7F;
        this->duration=0.7F;
        this->scale=Setting::SCALE/Random::GetRandomFloat(1.0F, 1.5F);
        this->x= x - static_cast<float>(IMG()->GetRegionWidth())/2.0F;
        this->y= y - static_cast<float>(IMG()->GetRegionHeight())/2.0F;
        this->angle=Random::GetRandomFloat(0.0F, 360.0F);
        this->scale2=1.0F;
    }

    void Hammer_effect::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        using namespace RUtil;
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
        r2->SetColor(RUtil::WHITE, this->color_a);
        r2->draw(IMG(), this->x + Random::GetRandomFloat(-2.0F, 2.0F)*Setting::SCALE, this->y + Random::GetRandomFloat(-2.0F, 2.0F)*Setting::SCALE, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), this->angle, static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, this->scale, this->scale);
        r2->SetColor(RUtil::WHITE, this->color_a/10.0F);
        r2->draw(IMG(), this->x, this->y, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), this->angle, static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, this->scale2, this->scale2);
    }

    void Hammer_effect::update(){
        this->color_a=this->duration;
        this->scale2=1.7F-this->duration;
        this->scale2*=this->scale2*this->scale2;
        this->scale+=DT/20.0F;
        TimeGo();
    }
} // namespace Effect
