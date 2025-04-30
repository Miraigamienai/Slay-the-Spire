#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"//father
#include "Game_object/card/Card_item.hpp"//member

namespace Action{
class Card_use_end_action final:public Actions
{
public:
    Card_use_end_action(const Card::Card_item &card_item):card_item(card_item){
        this->duration=0.15F;
    }
    ~Card_use_end_action() override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    const Card::Card_item card_item;
};
}