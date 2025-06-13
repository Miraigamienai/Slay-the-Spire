#include "Game_object/card/red/Wild_strike.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"//for accessing struct members
#include "Game_object/character/Monster/Monsters.hpp"//for passing the monsters to damage action
#include "Game_object/character/Player.hpp"//for passing the player to damage action
#include "Game_object/action/Damage_action.hpp"//for applying damage to the target
#include "Game_object/action/Show_card_to_draw_pile_action.hpp"
#include "Game_object/card/status/Wound.hpp"
#include "Game_object/Damage_info.hpp"//passes damage parameters

namespace Card{
namespace Red{
    void Wild_strike::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{this->damage, dungeon_shared.player, AttackType::slash_heavy}, target_monster));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_draw_pile_action>(std::make_shared<Card::Status::Wound>(), 1));
    }
}
}