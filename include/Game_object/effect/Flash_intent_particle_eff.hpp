#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReTexture.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "WindowSize.hpp"

namespace Effect{
class Flash_intent_particle_eff final:public Effects
{
public:
    Flash_intent_particle_eff(float x, float y, const std::shared_ptr<Draw::ReTexture>&img)noexcept
        :x(x), y(y), img(img)
    {
        duration=1.0F;
        scale=0.01F;   
    }
    ~Flash_intent_particle_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(RUtil::WHITE, duration/2.0F);
        r2->draw(img, x, y, static_cast<float>(img->GetWidth()), static_cast<float>(img->GetHeight()), 0.0F, static_cast<float>(img->GetWidth())/2.0F, static_cast<float>(img->GetHeight())/2.0F, scale, scale);
    }
    void update() override{
        scale=RUtil::Math::interpolation_fade(5.0F*Setting::SCALE, 0.01F, duration);
        TimeGo();
    }
private:
    const float x, y;
    const std::shared_ptr<Draw::ReTexture>&img;
};
}