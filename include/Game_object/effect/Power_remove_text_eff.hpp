#pragma once

#include "Game_object/effect/Effects.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace RUtil{
    enum class Powers_Text_ID:int;
    enum class AtlasRegionID:int;
}

namespace Effect{
class Power_remove_text_eff final:public Effects
{
public:
    Power_remove_text_eff(float x ,float y , RUtil::Powers_Text_ID power_text_id, RUtil::AtlasRegionID power_128_id)
        :x(x-64.0F*Setting::SCALE),
        y(y),
        offset_y(START_OFFSET_Y),
        power_text_id(power_text_id),
        power_128_id(power_128_id)
    {
        duration=DUR;
        scale=Setting::SCALE*0.7F;
        color_a=1.0F;
    }
    ~Power_remove_text_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float x,y;
    float offset_y;
    RUtil::Powers_Text_ID power_text_id;
    RUtil::AtlasRegionID power_128_id;
    static constexpr float DUR=2.0F,
                           START_OFFSET_Y=80.0F*Setting::SCALE,
                           TARGET_OFFSET_Y=160.0F*Setting::SCALE;
};
}