#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Border_flash_eff.hpp"
#include "Game_object/effect/Giant_fire_eff.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace EffectGen{
class Screen_on_fire_gen final:public Effect_gen
{
public:
    Screen_on_fire_gen()noexcept:gen_timer(0.0F){duration=DUR;}
    ~Screen_on_fire_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(duration==DUR){
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Border_flash_eff>(RUtil::ToRGBA(RUtil::Colors::FIREBRICK), Effect::Border_flash_eff::length::Long));
        }
        gen_timer-=DT;
        if(gen_timer<0.0F){
            gen_timer=GEN_TIME;
            for(int i=0;i<8;i++) dungeon_shared.effs.AddTop(std::make_shared<Effect::Giant_fire_eff>());
        }
        TimeGo();
    }
private:
    float gen_timer;
    static constexpr float DUR = 3.0F;
    static constexpr float GEN_TIME = 0.05F;
};
}