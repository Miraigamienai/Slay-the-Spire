#include "Game_object/card/red/Shrug_it_off.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Draw_card_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Card{
namespace Red{
    void Shrug_it_off::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &/* target_monster */){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(dungeon_shared.player, this->block));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Draw_card_action>(1));
    }
}
}