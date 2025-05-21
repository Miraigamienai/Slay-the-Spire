#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Flying_spike_eff.hpp"
#include "Game_object/effect/Effect_pool.hpp"
#include "Game_object/effect/Power_remove_text_eff.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "WindowSize.hpp"

namespace EffectGen{
using namespace Effect;
class Power_remove_text_gen final:public Effect_gen
{
public:
    Power_remove_text_gen(float x, float y, RUtil::Powers_Text_ID power_text_id, RUtil::AtlasRegionID power_128_id)noexcept
        :x(x-64.0F*Setting::SCALE),
        y(y),
        power_text_id(power_text_id),
        power_128_id(power_128_id)
    {
        duration=DUR;
    }
    ~Power_remove_text_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        using namespace RUtil;
        if(duration == Power_remove_text_eff::DUR*0.8F){
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_remove_text_eff>(x,y,power_text_id,power_128_id));
        }
        TimeGo();
        if(is_done){
            for(int i=0;i<10;i++)
                dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Flying_spike_eff>::GetEffect(x+Random::GetRandomFloat(50.0F, 70.0F)*Setting::SCALE, y+Random::GetRandomFloat(Power_remove_text_eff::START_OFFSET_Y, Power_remove_text_eff::TARGET_OFFSET_Y), Random::GetRandomFloat(50.0F, 400.0F)*Setting::SCALE, 0.0F, 0.0F, RUtil::BLUE_TEXT_COLOR));
            for(int i=0;i<10;i++)
                dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Flying_spike_eff>::GetEffect(x+Random::GetRandomFloat(0.0F, 20.0F)*Setting::SCALE, y+Random::GetRandomFloat(Power_remove_text_eff::START_OFFSET_Y, Power_remove_text_eff::TARGET_OFFSET_Y), -Random::GetRandomFloat(50.0F, 400.0F)*Setting::SCALE, 0.0F, 0.0F, RUtil::BLUE_TEXT_COLOR));
        }
    }
private:
    float x,y;
    RUtil::Powers_Text_ID power_text_id;
    RUtil::AtlasRegionID power_128_id;
    static constexpr float DUR=Power_remove_text_eff::DUR*0.8F;
};
}