#include "Game_object/effect/Draw_pile_glow_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG(int img_type)noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_p1))){
        switch(img_type){
            case 0:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_p1);
            case 1:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_p2);
            case 2:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_p3);
            case 3:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_p4);
            case 4:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_p5);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_ui_p6);
        }
    }

    using namespace RUtil;
    
    static constexpr auto CREAM_COLOR_VEC3 = Math::TO_VEC3(RUtil::CREAM_COLOR);
    
    Draw_pile_glow_eff::Draw_pile_glow_eff()
        :img_type(Random::GetRandomInt(6)),
        start_duration(Random::GetRandomFloat(2.0F, 5.0F)),
        x(Random::GetRandomFloat(35.0F, 85.0F)*Setting::SCALE - static_cast<float>(IMG(img_type)->GetRegionWidth())/2.0F),
        y(Random::GetRandomFloat(35.0F, 85.0F)*Setting::SCALE - static_cast<float>(IMG(img_type)->GetRegionHeight())/2.0F),
        speed_x(Random::GetRandomFloat(10.0F, 20.0F)*Setting::SCALE),
        speed_y(Random::GetRandomFloat(10.0F, 20.0F)*Setting::SCALE),
        flip_x(Random::GetRandomBoolean()),
        flip_y(Random::GetRandomBoolean()),
        angle_speed(Random::GetRandomFloat(-120.0F, 120.0F)),
        offset_x(0.0F),
        offset_y(0.0F),
        angle(0.0F)
    {
        duration=start_duration;
        float temp=Random::GetRandomFloat(0.1F, 0.4F);
        color=Math::GetColorUint32_RGB(CREAM_COLOR_VEC3.r-temp, CREAM_COLOR_VEC3.g-temp, CREAM_COLOR_VEC3.b-temp);
        scale=Setting::SCALE*0.75F;
        color_a=1.0F;
    }

    void Draw_pile_glow_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a);
        auto&img=IMG(img_type);
        r2->draw(img, x+offset_x, y+offset_y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, scale, scale);
    }

    void Draw_pile_glow_eff::update(){
        angle+=angle_speed*DT;
        if(speed_y!=0.0F){
            if(flip_y) y+=speed_y*DT;
            else y-=speed_y*DT;
            speed_y = Math::varlerp(speed_y, 0.0F, 0.25F, 0.5F);
        }
        if(speed_x!=0.0F){
            if(flip_x) x+=speed_x*DT;
            else x-=speed_x*DT;
            speed_x = Math::varlerp(speed_x, 0.0F, 0.25F, 0.5F);
        }
        color_a=duration/start_duration;
        TimeGo();
    }
} // namespace Effect
