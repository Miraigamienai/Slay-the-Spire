#include "Game_object/card/red/Strike_red.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"//for accessing struct members
#include "Game_object/character/Monster/Monsters.hpp"//for passing the monsters to damage action
#include "Game_object/character/Player.hpp"//for passing the player to damage action
#include "Game_object/action/Damage_action.hpp"//for applying damage to the target
#include "Game_object/Damage_info.hpp"//passes damage parameters

namespace Card{
namespace Red{
    void Strike_red::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster){
           //damage the monster
            dungeon_shared.action_group_handler.AddActionBot(
                std::make_shared<Action::Damage_action>
                (
                    Damage_info{this->damage, dungeon_shared.player, AttackType::slash_diagonal},
                    target_monster
                )
            );
    }
}
}