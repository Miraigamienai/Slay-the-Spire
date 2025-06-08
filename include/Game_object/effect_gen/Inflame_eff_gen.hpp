#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Exhaust_ember_eff.hpp"
#include "Game_object/effect/Flame_particle_eff.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace EffectGen{
class Inflame_eff_gen final:public Effect_gen
{
public:
    Inflame_eff_gen(float x, float y)noexcept:x(x),y(y){};
    ~Inflame_eff_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        for(int i=0;i<75;i++){
            if(RUtil::Random::GetRandomBoolean()) dungeon_shared.effs.AddTop(std::make_shared<Effect::Flame_particle_eff>(x, y));
            else dungeon_shared.back_effs.AddTop(std::make_shared<Effect::Flame_particle_eff>(x, y));
        }
        for(int i=0;i<20;i++) dungeon_shared.back_effs.AddTop(std::make_shared<Effect::Exhaust_ember_eff>(x, y));
        is_done=true;
    }
private:
    const float x, y;
};
}