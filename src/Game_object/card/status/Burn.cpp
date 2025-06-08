#include "Game_object/card/status/Burn.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"

namespace Card{
namespace Status{
    void Burn::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &/* target_monster */){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{this->magic_num, dungeon_shared.player, AttackType::fire}, dungeon_shared.player));
    }

    void Burn::OnEndOfTurn(Dungeon::Dungeon_shared &dungeon_shared){
        SetCanHoverInHand(false);
        Unhover();
        dungeon_shared.action_group_handler.AddCardQueue(Card_item{shared_from_this(), nullptr});      
    }
}
}