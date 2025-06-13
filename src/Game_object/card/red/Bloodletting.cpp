#include "Game_object/card/red/Bloodletting.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_energy_action.hpp"

namespace Card{
namespace Red{
    void Bloodletting::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{HP_LOSS, dungeon_shared.player, AttackType::NONE}, dungeon_shared.player, false));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_energy_action>(this->magic_num, true));
    }
}
}