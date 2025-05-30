#include "Game_object/effect/Stun_star_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect{
    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_tinyStar2))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_tinyStar2);
    }

    void Stun_star_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color_base, color_base*0.9F, color_base*0.3F, color_a);
        r2->draw(IMG(), x-offset_x*30.0F*Setting::SCALE, y-offset_y*5.0F*Setting::SCALE, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), angle, static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, Setting::SCALE, Setting::SCALE);
    }

    void Stun_star_eff::update(){
        offset_x=std::cos(glm::pi<float>()*duration);
        offset_y=std::cos(glm::two_pi<float>()*duration);
        angle-=DT*60.0F;
        if(duration>1.0F){
            color_base=RUtil::Math::Apply(0.0F, 1.0F, RUtil::Math::interpolation_powout(4, DUR-duration));
            color_a=RUtil::Math::Apply(0.0F, 1.0F, RUtil::Math::interpolation_powout(5, DUR-duration));
        }else{
            color_base=RUtil::Math::Apply(0.0F, 1.0F, RUtil::Math::interpolation_powout(2, duration));
            color_a=RUtil::Math::Apply(0.0F, 1.0F, RUtil::Math::interpolation_powout(5, duration));
        }
        TimeGo();
    }

    void Stun_star_eff::Initial(float x, float y){
        is_done=false;
        duration=DUR;
        color_a=0.0F;
        this->x= x - static_cast<float>(IMG()->GetRegionWidth())/2.0F;
        this->y= y - static_cast<float>(IMG()->GetRegionHeight())/2.0F;
        offset_x = offset_y = 1.0F;
        angle=RUtil::Random::GetRandomFloat(0.0F, 360.0F);
        color_base=0.0F;
    }
}