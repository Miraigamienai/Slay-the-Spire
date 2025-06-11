#include "Game_object/effect/Small_laser_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Random.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_laserThin))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_laserThin);
    }

    Small_laser_eff::Small_laser_eff(const glm::vec2 &start_pos,const glm::vec2 &target_pos)
        :start_x(start_pos.x),
        start_y(start_pos.y),
        distant(glm::distance(start_pos, target_pos)/Setting::SCALE),
        angle(RUtil::Math::GetDegress(target_pos - start_pos))
    {
        duration=DUR;
        color_a=0.0F;
    }
    
    void Small_laser_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(RUtil::ToRGBA(RUtil::Colors::CYAN), color_a);
        r2->draw(IMG(), start_x, start_y-static_cast<float>(IMG()->GetRegionHeight())/2.0F + 10.0F*Setting::SCALE, distant, 50.0F, angle, 0.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, Setting::SCALE + RUtil::Random::GetRandomFloat(-0.01F, 0.01F)*Setting::SCALE, Setting::SCALE);
        r2->SetColor(RUtil::Math::GetColorUint32_RGB(0.3F, 0.3F, 1.0F), color_a);
        r2->draw(IMG(), start_x, start_y-static_cast<float>(IMG()->GetRegionHeight())/2.0F, distant, RUtil::Random::GetRandomFloat(50.0F, 90.0F), angle, 0.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, Setting::SCALE + RUtil::Random::GetRandomFloat(-0.02F, 0.02F)*Setting::SCALE, Setting::SCALE);
    }

    void Small_laser_eff::update(){
        if(duration>DUR/2.0F) color_a=RUtil::Math::Apply(1.0F, 0.0F, std::pow((duration-0.25F)*4.0F, 2));
        else color_a=RUtil::Math::Apply(0.0F, 1.0F, RUtil::Math::BounceIn(duration*4.0F));
        TimeGo();
    }

} // namespace Effect
