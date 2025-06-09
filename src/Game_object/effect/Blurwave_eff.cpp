#include "Game_object/effect/Blurwave_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_blurWave))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_blurWave);
    }

    using namespace RUtil;
        
    Blurwave_eff::Blurwave_eff(float x, float y, Uint32 color)
        :wait_timer(Random::GetRandomFloat(0.0F, 0.3F)),
        speed_start(Random::GetRandomFloat(1000.0F, 1200.0F)*Setting::SCALE),
        speed_target(2000.0F*Setting::SCALE),
        speed(speed_start),
        x(x - static_cast<float>(IMG()->GetRegionWidth())/2.0F),
        y(y - static_cast<float>(IMG()->GetRegionHeight())/2.0F),
        angle(Random::GetRandomFloat(0.0F, 360.0F))
    {
        scale = Random::GetRandomFloat(0.5F, 0.9F);
        duration = DUR;
        auto color_temp=Math::TO_VEC3(color) - glm::vec3{0.0F, Random::GetRandomFloat(0.0F, 0.1F), Random::GetRandomFloat(0.0F, 0.2F)};
        this->color=Math::GetColorUint32_RGB(color_temp.r, color_temp.g, color_temp.b);
        color_a = 0.0F;
    }
    
    void Blurwave_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(color, color_a);
        r2->draw(IMG(), x, y, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), angle + 270.0F + Random::GetRandomFloat(-30.0F, 30.0F), static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, (this->scale + Random::GetRandomFloat(-0.08F, 0.08F))*Setting::SCALE, (this->scale + Random::GetRandomFloat(-0.08F, 0.08F))*Setting::SCALE);
    }

    void Blurwave_eff::update(){
        if(wait_timer>0.0F){
            wait_timer-=DT;
        }else{
            speed = Math::interpolation_fade(speed_start, speed_target, 1.0F-duration/DUR);
            x += std::cos(glm::radians(angle)) * speed;
            y += std::sin(glm::radians(angle)) * speed;
            scale *= 1.0F+DT*2.0F;
            if(duration>1.5F) color_a=Math::interpolation_fade(0.0F, 0.7F, (2.0F-duration)*2.0F);
            else if(duration<0.5F) color_a=Math::interpolation_fade(0.0F, 0.7F, duration*2.0F);
            TimeGo();
        }
    }
} // namespace Effect
