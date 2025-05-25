#pragma once

#include <memory>

#include "Game_object/effect_gen/Effect_gen.hpp"

//fwd decl
namespace Card{
    class Cards;
}

namespace EffectGen{
class Exhaust_card_eff_gen final:public Effect_gen
{
public:
    Exhaust_card_eff_gen(const std::shared_ptr<Card::Cards> &card)noexcept
        :card(card)
    {
        duration=DUR;
    }
    ~Exhaust_card_eff_gen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    std::shared_ptr<Card::Cards> card;
    static constexpr float DUR=1.0F;
};
}