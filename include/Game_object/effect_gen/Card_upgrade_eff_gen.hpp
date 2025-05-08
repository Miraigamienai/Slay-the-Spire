#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"

namespace EffectGen{
class Card_upgrade_eff_gen final:public Effect_gen
{
public:
    Card_upgrade_eff_gen(float x,float y)noexcept:x(x),y(y),one(false),two(false){
        this->duration=0.8F;
    }
    ~Card_upgrade_eff_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    float x,y;
    bool one,two;
};
}