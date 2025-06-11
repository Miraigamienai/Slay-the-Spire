#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Border_flash_eff.hpp"
#include "Game_object/effect/Intense_zoom_particle.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace EffectGen{
class Intense_zoom_gen final:public Effect_gen
{
public:
    Intense_zoom_gen(float x, float y):x(x),y(y){};
    ~Intense_zoom_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        dungeon_shared.effs.AddTop(std::make_shared<Effect::Border_flash_eff>(RUtil::GOLD_COLOR, Effect::Border_flash_eff::length::Normal, false));
        for(int i=0;i<10;i++)
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Intense_zoom_particle>(x, y));
        is_done=true;
    }
private:
    const float x, y;
};
}