#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"//father
#include "Game_object/card/Card_item.hpp"//member

//fwd decl
namespace Character{
    class Characters;
}

namespace Action{
class Card_use_action final:public Actions
{
public:
    Card_use_action(const Card::Card_item &card_item, const std::shared_ptr<Character::Characters> &target);
    ~Card_use_action() override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    Card::Card_item card_itme;
    std::shared_ptr<Character::Characters> target;
};
}