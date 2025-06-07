#include "Game_object/effect/Light_flare_particle_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Random.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_blurDot))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_blurDot);
    }

    Light_flare_particle_eff::Light_flare_particle_eff(float x, float y, Uint32 color_rgb)
        :x(x - static_cast<float>(IMG()->GetRegionWidth())/2.0F),
        y(y - static_cast<float>(IMG()->GetRegionHeight())/2.0F),
        angle(RUtil::Random::GetRandomFloat(0.0F, 360.0F)),
        speed(RUtil::Random::GetRandomFloat(200.0F, 300.0F)*Setting::SCALE),
        speed_start(speed),
        speed_target(RUtil::Random::GetRandomFloat(0.1F, 0.5F)*Setting::SCALE),
        start_duration(RUtil::Random::GetRandomFloat(0.5F, 1.1F)),
        wave_speed(RUtil::Random::GetRandomFloat(-20.0F, 20.0F)),
        wave_height(RUtil::Random::GetRandomFloat(5.0F, 10.0F))
    {
        duration=start_duration;
        color_a=1.0F;
        color=color_rgb;
        scale=RUtil::Random::GetRandomFloat(0.2F, 1.0F)*Setting::SCALE;
    }

    void Light_flare_particle_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(color, color_a/4.0F);
        r2->draw(IMG(), x, y, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), angle, static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, this->scale*4.0F, this->scale*4.0F);
        r2->SetColor(color, color_a);
        r2->draw(IMG(), x, y, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), angle, static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, this->scale, this->scale);
    }

    void Light_flare_particle_eff::update(){
        speed = RUtil::Math::Apply(speed_start, speed_target, 1.0F-std::sqrt(duration/start_duration));
        x += std::cos(angle)*speed*DT;
        y += std::sin(angle)*speed*DT;
        angle += std::cos(duration * wave_speed) * wave_height;
        if(duration<0.5F) color_a=RUtil::Math::interpolation_fade(0.0F, 1.0F, duration*2.0F);
        TimeGo();
    }
} // namespace Effect
