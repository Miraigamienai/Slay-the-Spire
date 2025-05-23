#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Power_buff_debuff_eff.hpp"
#include "Game_object/effect/Effect_pool.hpp"
#include "Game_object/effect/Flying_spike_eff.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/power/Powers.hpp"
#include "RUtil/Random.hpp"

#include "Util/Logger.hpp"

namespace EffectGen{
static constexpr inline float color_norm(Uint32 x)noexcept{return static_cast<float>(x)/255.0F;}
static constexpr inline glm::vec3 TO_VEC3(Uint32 color){
    return glm::vec3{
        color_norm((color&0xff000000)>>24),
        color_norm((color&0x00ff0000)>>16),
        color_norm((color&0x0000ff00)>>8)
    };
}
class Power_buff_debuff_gen final:public Effect_gen
{
public:
    Power_buff_debuff_gen(float x, float y, RUtil::Powers_Text_ID power_id, int amount, Power::PowerType power_type, bool already_have)
        :x(x),
        y(y),
        power_id(power_id),
        amount(amount),
        power_type(power_type),
        already_have(already_have)
    {}
    ~Power_buff_debuff_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(amount==0){
            LOG_ERROR("Power_buff_debuff_gen class receive amount 0");
            is_done=true;
            return;
        }
        using namespace RUtil;
        if(power_type==Power::PowerType::buff || (power_type==Power::PowerType::neutral&&amount>0)){
            for(int i=0;i<10;i++) dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Flying_spike_eff>::GetEffect(x + Random::GetRandomFloat(-120.0F, 120.0F)*Setting::SCALE, y + Random::GetRandomFloat(90.0F, 110.0F)*Setting::SCALE, 0.0F, Random::GetRandomFloat(50.0F, 200.0F)*Setting::SCALE, 90.0F, RUtil::GREEN_TEXT_COLOR));
            for(int i=0;i<10;i++) dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Flying_spike_eff>::GetEffect(x + Random::GetRandomFloat(-120.0F, 120.0F)*Setting::SCALE, y + Random::GetRandomFloat(90.0F, 110.0F)*Setting::SCALE, 0.0F, -Random::GetRandomFloat(50.0F, 200.0F)*Setting::SCALE, -90.0F, RUtil::GREEN_TEXT_COLOR));
            if(already_have)
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_buff_debuff_eff>(x, y, power_id, amount, GREEN_TEXT_RGB));
            else
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_buff_debuff_eff>(x, y, power_id, GREEN_TEXT_RGB));
        }else{
            for(int i=0;i<10;i++) dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Flying_spike_eff>::GetEffect(x - Random::GetRandomFloat(0.0F, 20.0F)*Setting::SCALE, y + Random::GetRandomFloat(40.0F, 160.0F)*Setting::SCALE, Random::GetRandomFloat(50.0F, 400.0F)*Setting::SCALE, 0.0F, Random::GetRandomFloat(0.0F, 360.0F), RUtil::RED_TEXT_COLOR));
            for(int i=0;i<10;i++) dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Flying_spike_eff>::GetEffect(x + Random::GetRandomFloat(0.0F, 20.0F)*Setting::SCALE, y + Random::GetRandomFloat(40.0F, 160.0F)*Setting::SCALE, -Random::GetRandomFloat(50.0F, 400.0F)*Setting::SCALE, 0.0F, Random::GetRandomFloat(0.0F, 360.0F), RUtil::RED_TEXT_COLOR));
            if(already_have)
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_buff_debuff_eff>(x, y, power_id, amount, RED_TEXT_RGB));
            else
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_buff_debuff_eff>(x, y, power_id, RED_TEXT_RGB));
        }
        is_done=true;
    }
private:
    const float x,y;
    const RUtil::Powers_Text_ID power_id;
    const int amount;
    const Power::PowerType power_type;
    const bool already_have;
    static constexpr auto RED_TEXT_RGB=TO_VEC3(RUtil::RED_TEXT_COLOR),
                          GREEN_TEXT_RGB=TO_VEC3(RUtil::GREEN_TEXT_COLOR);
};
}