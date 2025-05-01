#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"//father
#include "Game_object/card/Card_item.hpp"//member

//fwd decl
namespace Monster{
    class Monster_group;
}

namespace Action{
class Card_use_start_action final:public Actions
{
public:
    Card_use_start_action(const Card::Card_item &card_item, const Monster::Monster_group&room_monsters);
    ~Card_use_start_action() override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    const Card::Card_item card_itme;
    const Monster::Monster_group&room_monsters;
};
}