#pragma once

#include "Game_object/effect/Effects.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "WindowSize.hpp"

namespace Effect{
using namespace RUtil;    
class Empower_circle_eff final:public Effects
{
public:
    Empower_circle_eff(float x, float y)
        :img_type(Random::GetRandomBoolean()),
        x(x - static_cast<float>(All_Image::GetAtlasRegion(IMG_ID(img_type))->GetRegionWidth())/2.0F),
        y(y - static_cast<float>(All_Image::GetAtlasRegion(IMG_ID(img_type))->GetRegionHeight())/2.0F),
        speed_x(Random::GetRandomFloat(-6000.0F*Setting::SCALE, 6000.0F*Setting::SCALE)),
        speed_y(Random::GetRandomFloat(-6000.0F*Setting::SCALE, 6000.0F*Setting::SCALE)),
        angle(Math::GetDegress(glm::vec2{speed_x, speed_y})),
        start_duration(Random::GetRandomFloat(0.8F, 3.2F))
    {
        this->duration=this->start_duration;
        this->color=Random::GetRandomBoolean() ? RUtil::CREAM_COLOR : ToRGBA(Colors::SLATE_GRAY);
        this->color_a=1.0F;
        this->scale=Setting::SCALE;
    }
    ~Empower_circle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(this->color, this->color_a);
        auto&img=All_Image::GetAtlasRegion(IMG_ID(img_type));
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale*Random::GetRandomFloat(0.9F, 1.1F), this->scale*Random::GetRandomFloat(0.9F, 1.1F));
    }
    void update() override{
        x+=speed_x*DT;
        y+=speed_y*DT;
        speed_x=Math::fadelerp(speed_x, 0.0F);
        speed_y=Math::fadelerp(speed_y, 0.0F);
        scale=Setting::SCALE*duration/start_duration;
        if(duration<start_duration/2.0F) color_a=duration/(start_duration/2.0F);
        TimeGo();
    }
private:
    const bool img_type;
    float x, y;
    float speed_x, speed_y;
    const float angle;
    const float start_duration;
    static constexpr AtlasRegionID IMG_ID(bool img_type){return img_type ? AtlasRegionID::_combat_empowerCircle1 : AtlasRegionID::_combat_empowerCircle2;}
};
}