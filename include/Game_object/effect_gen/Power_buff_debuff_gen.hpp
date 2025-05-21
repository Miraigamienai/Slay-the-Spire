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
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_buff_debuff_eff>(x, y, power_id, amount, RUtil::GREEN_TEXT_COLOR));
            else
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_buff_debuff_eff>(x, y, power_id, RUtil::GREEN_TEXT_COLOR));
        }else{
            for(int i=0;i<10;i++) dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Flying_spike_eff>::GetEffect(x - Random::GetRandomFloat(0.0F, 20.0F)*Setting::SCALE, y + Random::GetRandomFloat(40.0F, 160.0F)*Setting::SCALE, Random::GetRandomFloat(50.0F, 400.0F)*Setting::SCALE, 0.0F, Random::GetRandomFloat(0.0F, 360.0F), RUtil::RED_TEXT_COLOR));
            for(int i=0;i<10;i++) dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Flying_spike_eff>::GetEffect(x + Random::GetRandomFloat(0.0F, 20.0F)*Setting::SCALE, y + Random::GetRandomFloat(40.0F, 160.0F)*Setting::SCALE, -Random::GetRandomFloat(50.0F, 400.0F)*Setting::SCALE, 0.0F, Random::GetRandomFloat(0.0F, 360.0F), RUtil::RED_TEXT_COLOR));
            if(already_have)
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_buff_debuff_eff>(x, y, power_id, amount, RUtil::RED_TEXT_COLOR));
            else
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Power_buff_debuff_eff>(x, y, power_id, RUtil::RED_TEXT_COLOR));
        }
        is_done=true;
    }
private:
    const float x,y;
    const RUtil::Powers_Text_ID power_id;
    const int amount;
    const Power::PowerType power_type;
    const bool already_have;
};
}