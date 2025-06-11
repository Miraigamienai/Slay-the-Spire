#include "Game_object/effect/Cleave_eff.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "WindowSize.hpp"

namespace Effect{
    using namespace RUtil;

    static SETTING_CONSTEXPR float SPEED_X = 100.0F*Setting::SCALE; 

    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_cleave))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_cleave);
    }

    Cleave_eff::Cleave_eff(float x, float y)
        :wait_timer(Random::GetRandomFloat(0.0F, 0.2F)),
        x(x - static_cast<float>(IMG()->GetRegionWidth())/2.0F),
        y(y - static_cast<float>(IMG()->GetRegionHeight())/2.0F),
        angle(Random::GetRandomFloat(-5.0F, 1.0F))
    {
        scale = Setting::SCALE*1.2F;
        color_a = 0.0F;
        duration = FADE_IN_TIME + FADE_OUT_TIME;
    }

    void Cleave_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(RUtil::WHITE, color_a);
        r2->draw(IMG(), x, y, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), angle, static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, this->scale, this->scale);
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->draw(IMG(), x, y, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), angle, static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, this->scale, this->scale);
    }

    void Cleave_eff::update(){
        if(wait_timer>0.0F){
            wait_timer-=DT;
        }else{
            x += SPEED_X*DT;
            angle += Random::GetRandomFloat(-0.5F, 0.5F);
            scale += 0.3F*Setting::SCALE*DT;
            if(duration>FADE_OUT_TIME)
                color_a = Math::interpolation_fade(1.0F, 0.0F, (duration-FADE_OUT_TIME)/FADE_IN_TIME);
            else
                color_a = Math::interpolation_pow2(0.0F, 1.0F, duration/FADE_OUT_TIME);
            TimeGo();
        }
    }
}