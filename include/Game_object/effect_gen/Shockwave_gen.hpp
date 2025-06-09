#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Blurwave_eff.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace EffectGen{
class Shockwave_gen final:public Effect_gen
{
public:
    Shockwave_gen(float x, float y, Uint32 color)noexcept:x(x),y(y),color(color){}
    ~Shockwave_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        for(int i=0;i<40;i++){
            if(RUtil::Random::GetRandomBoolean())
                dungeon_shared.effs.AddTop(std::make_shared<Effect::Blurwave_eff>(x, y, color));
            else
                dungeon_shared.back_effs.AddTop(std::make_shared<Effect::Blurwave_eff>(x, y, color));
        }
        is_done=true;
    }
private:
    const float x, y;
    const Uint32 color;
};
}