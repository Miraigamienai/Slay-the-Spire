#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect_gen/Show_card_to_discard.hpp"

namespace Action{
class Show_card_to_discard_action final:public Actions
{
public:
    Show_card_to_discard_action(const std::shared_ptr<Card::Cards> &card, int num = 1)noexcept:card(card),num(num){
        this->duration=DUR;
    }
    ~Show_card_to_discard_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(duration==DUR){
            for(int i=0;i<num;i++) dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Show_card_to_discard>(card));
        }
        TimeGo();
    }
private:
    const std::shared_ptr<Card::Cards> card;
    const int num;
    static constexpr float DUR=0.5F;
};
}