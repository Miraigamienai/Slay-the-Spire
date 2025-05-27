#pragma once

#include <memory>

#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/effect/Empower_circle_eff.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/card/Cards.hpp"

namespace EffectGen{
class Empower_circle_gen final:public Effect_gen
{
public:
    Empower_circle_gen(const std::shared_ptr<Card::Cards> &card, float x, float y)noexcept:card(card),x(x),y(y){}
    ~Empower_circle_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        //wait until card is not flying;
        if(!card->is_fly()){
            for(int i=0;i<18;i++)
                dungeon_shared.back_effs.AddTop(std::make_shared<Effect::Empower_circle_eff>(x, y));
            is_done=true;
        }
    }
private:
    std::shared_ptr<Card::Cards> card;
    const float x,y;
};
}