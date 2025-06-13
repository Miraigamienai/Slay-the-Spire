#include "Game_object/card/red/Power_through.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"//for accessing struct members
#include "Game_object/character/Monster/Monsters.hpp"//for passing the monsters to damage action
#include "Game_object/character/Player.hpp"//for passing the player to damage action
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Show_card_to_hand_action.hpp"
#include "Game_object/card/status/Wound.hpp"
#include "Game_object/Damage_info.hpp"//passes damage parameters

namespace Card{
namespace Red{
    void Power_through::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters>  & /*target_monster */){

        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(dungeon_shared.player, this->block));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_hand_action>(std::make_shared<Card::Status::Wound>(), 2));
    }
}
}