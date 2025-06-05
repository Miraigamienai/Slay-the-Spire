#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Flash_intent_particle_eff.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace EffectGen{
class Flash_intent_particle_gen final:public Effect_gen
{
public:
    Flash_intent_particle_gen(float x, float y, const std::shared_ptr<Draw::ReTexture>&img)noexcept
        :x(x), y(y), img(img), gen_timer(0.0F)
    {
        duration=1.0F;
    }
    ~Flash_intent_particle_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        gen_timer-=DT;
        if(gen_timer<0.0F){
            gen_timer=GEN_TIME;
            dungeon_shared.back_effs.AddTop(std::make_shared<Effect::Flash_intent_particle_eff>(x, y, img));
        }
        TimeGo();
    }
private:
    const float x, y;
    const std::shared_ptr<Draw::ReTexture>&img;
    float gen_timer;
    static constexpr float GEN_TIME=0.17F;

};
}