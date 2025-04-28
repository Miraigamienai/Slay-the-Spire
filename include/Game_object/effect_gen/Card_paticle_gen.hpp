#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Card_proof_particle.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Effect_pool.hpp"

namespace EffectGen{
class Card_paticle_gen final:public Effect_gen
{
public:
    Card_paticle_gen(float x,float y){
        this->duration=x;//durration is x here.
        this->y=y;
    }
    ~Card_paticle_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        for(int i=0;i<50;i++) dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Card_proof_particle>::GetEffect(this->duration, this->y));
        this->is_done=true;
    }
private:
    float y;
};
}