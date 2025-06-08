#pragma once

#include <memory>

#include "Game_object/effect_gen/Effect_gen.hpp"

//fwd decl
namespace Card{
    class Cards;
}

namespace EffectGen{
class Show_card_to_draw_pile final:public Effect_gen
{
public:
    Show_card_to_draw_pile(const std::shared_ptr<Card::Cards> &card);
    ~Show_card_to_draw_pile()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    std::shared_ptr<Card::Cards> card;
    static int s_cnt;
};
}