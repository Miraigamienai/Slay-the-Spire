#include "Game_object/effect/Weighty_impact_eff.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_weightyImpact))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_weightyImpact);
    }
    static inline auto IMG_H_W()noexcept(noexcept(IMG()) && noexcept(IMG()->GetRegionWidth())){
        return static_cast<float>(IMG()->GetRegionWidth())/2.0F;
    }
    static inline auto IMG_H_H()noexcept(noexcept(IMG()) && noexcept(IMG()->GetRegionHeight())){
        return static_cast<float>(IMG()->GetRegionHeight())/2.0F;
    }
    Weighty_impact_eff::Weighty_impact_eff(float x, float y, float color_r, float color_b)noexcept
        :x(x-IMG_H_W()),
        y(static_cast<float>(Setting::WINDOW_HEIGHT)-IMG_H_H()),
        r(color_r),
        b(color_b),
        angle(RUtil::Random::GetRandomFloat(-1.0F, 1.0F)),
        target_y(y-180.0F*Setting::SCALE)
    {
        duration=DUR;
        scale=Setting::SCALE;
        color_a=0.0F;
    }
    void Weighty_impact_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(r, 1.0F, b, color_a);
        r2->draw(IMG(), x, y+140.0F*Setting::SCALE, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight())*(duration+0.2F)*5.0F, angle, IMG_H_W(), IMG_H_H(), scale*RUtil::Random::GetRandomFloat(0.99F, 1.01F)*0.3F, scale*RUtil::Random::GetRandomFloat(0.99F, 1.01F)*2.0F*(duration+0.8F));
        r2->SetColor(r, 0.6F, b, color_a);
        r2->draw(IMG(), x, y+40.0F*Setting::SCALE,  static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight())*(duration+0.2F)*5.0F, angle, IMG_H_W(), IMG_H_H(), scale*RUtil::Random::GetRandomFloat(0.99F, 1.01F)*0.7F, scale*RUtil::Random::GetRandomFloat(0.99F, 1.01F)*1.3F*(duration+0.8F));
        r2->SetColor(r, 0.2F, b, color_a);
        r2->draw(IMG(), x, y,                       static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight())*(duration+0.2F)*5.0F, angle, IMG_H_W(), IMG_H_H(), scale*RUtil::Random::GetRandomFloat(0.99F, 1.01F), scale*RUtil::Random::GetRandomFloat(0.99F, 1.01F)*(duration+0.8F));
    }
    void Weighty_impact_eff::update(){
        y=RUtil::Math::interpolation_fade(static_cast<float>(Setting::WINDOW_HEIGHT), target_y, DUR-duration);
        scale+=RUtil::Game_Input::delta_time();
        if(duration<0.2F)
            color_a=0.5F;
        else
            color_a=RUtil::Math::interpolation_powout2(0.6F, 0.0F, duration);
        TimeGo();
    }
} // namespace Effect
