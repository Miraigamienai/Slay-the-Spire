#pragma once

#include <memory>

#include "Game_object/effect_gen/Effect_gen.hpp"

//fwd decl
namespace Card{
    class Cards;
}

namespace EffectGen{
class Purge_card_eff_gen final:public Effect_gen
{
public:
    Purge_card_eff_gen(const std::shared_ptr<Card::Cards> &card);
    ~Purge_card_eff_gen()override{--s_cnt;}
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    std::shared_ptr<Card::Cards> card;
    bool first;
    static int s_cnt;
};
}