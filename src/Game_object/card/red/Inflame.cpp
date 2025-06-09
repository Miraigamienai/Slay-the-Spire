#include "Game_object/card/red/Inflame.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"//for accessing struct members
#include "Game_object/character/Monster/Monsters.hpp"//for passing the monsters to damage action
#include "Game_object/character/Player.hpp"//for passing the player to damage action
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/Damage_info.hpp"//passes damage parameters

namespace Card{
namespace Red{
    void Inflame::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, this->magic_num, dungeon_shared.player, dungeon_shared.player));
        
    
    }
}
}