#include <array>

#include "Game_object/effect/Discard_glow_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect{
    static constexpr std::array<glm::vec2, 10> ABOVE_POS{{{1886.0F, 86.0F}, {1883.0F, 80.0F}, {1881.0F, 67.0F}, {1876.0F, 54.0F}, {1873.0F, 45.0F}, {1865.0F, 36.0F}, {1849.0F, 32.0F}, {1841.0F, 36.0F}, {1830.0F, 36.0F}, {1819.0F, 43.0F}}};
    static constexpr std::array<glm::vec2, 10> BELOW_POS{{{1810.0F, 84.0F}, {1820.0F, 88.0F}, {1830.0F, 94.0F}, {1834.0F, 96.0F}, {1837.0F, 96.0F}, {1841.0F, 98.0F}, {1854.0F, 99.0F}, {1859.0F, 91.0F}, {1871.0F, 87.0F}, {1877.0F, 84.0F}}};
    static constexpr auto DISCARD_COLOR_VEC3 = RUtil::Math::TO_VEC3(RUtil::DISCARD_COLOR);

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
    
    Discard_glow_eff::Discard_glow_eff(bool is_above)
        :img_type(Random::GetRandomInt(6)),
        pos((is_above ? ABOVE_POS : BELOW_POS)[Random::GetRandomInt(static_cast<int>(ABOVE_POS.size()))]*Setting::SCALE - glm::vec2{static_cast<float>(IMG(img_type)->GetRegionWidth()), static_cast<float>(IMG(img_type)->GetRegionHeight())}/2.0F),
        start_duration(Random::GetRandomFloat(0.4F, 0.9F)),
        scale_jitter(Random::GetRandomFloat(0.9F, 1.1F)),
        speed_y(Random::GetRandomFloat(30.0F, 60.0F)*Setting::SCALE),
        is_additive(Random::GetRandomBoolean()),
        angle_speed(Random::GetRandomFloat(-180.0F, 180.0F)),
        offset_x(0.0F),
        offset_y(0.0F),
        angle(0.0F)
    {
        duration=start_duration;
        color=Math::GetColorUint32_RGB(DISCARD_COLOR_VEC3.r-Random::GetRandomFloat(0.0F, 0.1F), DISCARD_COLOR_VEC3.g+Random::GetRandomFloat(0.0F, 0.1F), DISCARD_COLOR_VEC3.b+Random::GetRandomFloat(0.0F, 0.1F));
        scale=Setting::SCALE;
        color_a=1.0F;
    }

    void Discard_glow_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(is_additive) r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        else r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a);
        auto &img=IMG(img_type);
        r2->draw(img, pos.x+offset_x, pos.y+offset_y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, scale*scale_jitter, scale*scale_jitter);
    }

    void Discard_glow_eff::update(){
        angle+=angle_speed*DT;
        pos.y+=speed_y*DT;
        if(duration<0.1F) scale=Setting::SCALE*(duration/start_duration*2.0F+0.5F);
        if(duration<0.25F) color_a=duration*4.0F;
        TimeGo();
    }
}