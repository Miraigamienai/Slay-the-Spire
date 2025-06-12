#include "Game_object/card/red/Bash.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/action/Damage_action.hpp"//for applying damage to the target
#include "RUtil/Powers_Text_Reader.hpp"

namespace Card{
namespace Red{
    void Bash::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster){
        dungeon_shared.action_group_handler.AddActionBot(
            std::make_shared<Action::Damage_action>
            (
                Damage_info{this->damage, dungeon_shared.player, AttackType::slash_diagonal},
                target_monster
            )
        );

        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Vulnerable, this->magic_num, dungeon_shared.player, target_monster));
        
    }
}
}