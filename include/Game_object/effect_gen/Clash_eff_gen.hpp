#pragma once

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Effect_pool.hpp"
#include "Game_object/effect/Shine_particle.hpp"
#include "Game_object/effect/Slash_eff.hpp"
#include "RUtil/ColorValuesOnly.hpp"

namespace EffectGen{
class Clash_eff_gen final:public Effect_gen
{
public:
    Clash_eff_gen(float x,float y)noexcept:x(x),y(y){
        this->duration=0.1F;
    }
    ~Clash_eff_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        using namespace Effect;
        dungeon_shared.effs.AddTop(Effect_pool<Slash_eff>::GetEffect(glm::vec2{this->x, this->y-30.0F*Setting::SCALE}, glm::vec2{-500.0F, -500.0F}, 135.0F, 4.0F, RUtil::SCARLET, RUtil::ToRGBA(RUtil::Colors::GOLD)));
        dungeon_shared.effs.AddTop(Effect_pool<Slash_eff>::GetEffect(glm::vec2{this->x, this->y-30.0F*Setting::SCALE}, glm::vec2{500.0F, -500.0F}, 225.0F, 4.0F, RUtil::ToRGBA(RUtil::Colors::SKY_BLUE), RUtil::ToRGBA(RUtil::Colors::CYAN)));
        for(int i=0;i<15;++i){
            dungeon_shared.effs.AddTop(Effect_pool<Shine_particle>::GetEffect(this->x, this->y, 40.0F));
        }
        is_done=true;
    }
private:
    float x,y;
};
}