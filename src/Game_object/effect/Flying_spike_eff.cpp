#include "Game_object/effect/Flying_spike_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect{

    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_spike))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_spike);
    }

    Flying_spike_eff::Flying_spike_eff(float x, float y, float speed_x, float speed_y, Uint32 color)
        :x(x-static_cast<float>(IMG()->GetRegionWidth())/2.0F),
        y(y-static_cast<float>(IMG()->GetRegionHeight())/2.0F),
        speed_x(speed_x),
        speed_y(speed_y),
        angle(RUtil::Random::GetRandomFloat(-5.0F, 5.0F))
    {
        this->duration=DUR;
        this->color=color;
        this->color_a=0.0F;
        this->scale=DUR*2.0F*Setting::SCALE;
    }
    
    void Flying_spike_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
        r2->SetColor(this->color, this->color_a);
        r2->draw(IMG(), this->x, this->y, static_cast<float>(IMG()->GetRegionWidth()), static_cast<float>(IMG()->GetRegionHeight()), this->angle, static_cast<float>(IMG()->GetRegionWidth())/2.0F, static_cast<float>(IMG()->GetRegionHeight())/2.0F, this->scale, this->scale);
    }
    
    void Flying_spike_eff::update(){
        this->scale=duration*2.0F*Setting::SCALE;
        this->x+=speed_x*DT;
        this->y+=speed_y*DT;
        this->color_a= duration>0.5F ? (DUR-duration)*2.0F : duration;
        TimeGo();
    }
}