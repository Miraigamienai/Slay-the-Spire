#pragma once

#include <memory>

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Vertical_aura.hpp"
#include "Game_object/effect/Effect_pool.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace EffectGen{
class Vertical_aura_gen final:public Effect_gen
{
public:
    Vertical_aura_gen(Uint32 color,float x,float y)noexcept:
        color(color),x(x)
    {
        this->duration=y;//NOTE:'duration' is used to store the y-position..
    }
    ~Vertical_aura_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        for(int i=0;i<20;i++){
            dungeon_shared.back_effs.AddTop(Effect::Effect_pool<Effect::Vertical_aura>::GetEffect(color, x, duration/* this duration is y */));
        }
        is_done=true;//immediately done
    }
private:
    Uint32 color;
    float x;
};
}