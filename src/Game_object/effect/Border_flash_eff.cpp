#include "Game_object/effect/Border_flash_eff.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto &IMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_borderGlow2))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_borderGlow2);
    }

    Border_flash_eff::Border_flash_eff(Uint32 color, length len, bool addtive)
        :addtive(addtive),
        start_duration(len==length::Long ? DUR*2.0F : DUR)
    {
        duration= start_duration;
        color_a=0.0F;
        this->color=color;
    }

    void Border_flash_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(addtive) r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        else r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a);
        r2->draw(IMG(), 0.0F, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT));
    }

    void Border_flash_eff::update(){
        if(start_duration - duration < start_duration/10.0F) color_a=RUtil::Math::interpolation_fade(0.0F, 1.0F, (start_duration-duration)/(start_duration/10.0F));
        else color_a=RUtil::Math::interpolation_powout2(0.0F, 1.0F, duration/start_duration);
        TimeGo();
    }
} // namespace Effect
