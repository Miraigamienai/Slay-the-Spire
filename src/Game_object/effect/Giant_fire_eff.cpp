#include "Game_object/effect/Giant_fire_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame4))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame4);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame5);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_flame6);
        }
    }

    using namespace RUtil;

    Giant_fire_eff::Giant_fire_eff()
        :img_type(Random::GetRandomInt(3)),
        x(Random::GetRandomFloat(0.0F, static_cast<float>(Setting::WINDOW_WIDTH)) - static_cast<float>(IMG(img_type)->GetRegionWidth())/2.0F),
        y(Random::GetRandomFloat(-200.0F, -400.0F)*Setting::SCALE - static_cast<float>(IMG(img_type)->GetRegionHeight())/2.0F),
        speed_x(Random::GetRandomFloat(-70.0F, 70.0F)*Setting::SCALE),
        speed_y(Random::GetRandomFloat(500.0F, 1700.0F)*Setting::SCALE),
        angle(Random::GetRandomFloat(-10.0F, 10.0F)),
        flip_x(Random::GetRandomBoolean()),
        delay_timer(Random::GetRandomFloat(0.0F, 0.1F)),
        target_a(Random::GetRandomFloat(0.2F, 0.6F))
    {
        duration=DUR;
        scale=Random::GetRandomFloat(0.5F, 7.0F);
        color_a = 0.0F;
        const float g = Random::GetRandomFloat(0.5F, 1.0F);
        color = Math::GetColorUint32_RGB(1.0F, g, g-Random::GetRandomFloat(0.0F, 0.2F));
    }

    void Giant_fire_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(color, color_a);
        auto &img=IMG(img_type);
        r2->draw(img, x, y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale*Setting::SCALE, this->scale*Setting::SCALE);
    }

    void Giant_fire_eff::update(){
        if(delay_timer>0.0F) delay_timer-=DT;
        else{
            x+=speed_x*DT;
            y+=speed_y*DT;
            scale*=Random::GetRandomFloat(0.95F, 1.05F);
            if(DUR-duration<0.75F){
                color_a=Math::interpolation_fade(0.0F, target_a, (DUR-duration)/0.75F);
            }else{
                color_a=Math::interpolation_fade(0.0F, target_a, duration/0.75F);
            }
        }
        TimeGo();
    }
} // namespace Effect
