#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Fire_burst_particle_eff.hpp"
#include "Game_object/effect/Light_flare_particle_eff.hpp"
#include "RUtil/ColorValuesOnly.hpp"

namespace EffectGen{
class Ghost_ignite_gen final:public Effect_gen
{
public:
    Ghost_ignite_gen(float x,float y)noexcept:x(x),y(y){}
    ~Ghost_ignite_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        for(int i=0;i<25;i++){
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Fire_burst_particle_eff>(x, y));
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Light_flare_particle_eff>(x, y, RUtil::ToRGBA(RUtil::Colors::CHARTREUSE)));
        }
        is_done=true;
    }
private:
    const float x,y;
};
}