#pragma once

#include <memory>

#include "Game_object/effect/Effects.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "WindowSize.hpp"

namespace Effect{
class Flash_power_eff final:public Effects
{
public:
    Flash_power_eff(float x, float y, RUtil::AtlasRegionID power_128_id)
        :x(x),y(y),power_128_id(power_128_id)
    {
        this->duration=DUR;
        this->color_a=1.0F;
        this->scale=Setting::SCALE*0.3F;
    }
    ~Flash_power_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(RUtil::WHITE, this->color_a);
        auto&img=RUtil::All_Image::GetAtlasRegion(power_128_id);
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), 0.0F, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale*3.0F, this->scale*3.0F);
    }
    void update()override{
        if(duration<DUR/2.0F) color_a=duration/(DUR/2.0F);
        this->scale=RUtil::Math::interpolation_exp5in(Setting::SCALE, Setting::SCALE*0.3F, duration/DUR);
        TimeGo();
    }
private:
    const float x,y;
    const RUtil::AtlasRegionID power_128_id;
    static constexpr float DUR = 0.7F;
};
}
