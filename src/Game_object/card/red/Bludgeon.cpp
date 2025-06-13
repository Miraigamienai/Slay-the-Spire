#include "Game_object/card/red/Bludgeon.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"//for accessing struct members
#include "Game_object/character/Monster/Monsters.hpp"//for passing the monsters to damage action
#include "Game_object/character/Player.hpp"//for passing the player to damage action
#include "Game_object/action/Damage_action.hpp"//for applying damage to the target
#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "Game_object/effect_gen/Weighty_impact_gen.hpp"

namespace Card{
namespace Red{
    void Bludgeon::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Weighty_impact_gen>(target_monster->GetcX(), target_monster->GetcY(), 1.0F, 0.1F), 0.8F));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{this->damage, dungeon_shared.player, AttackType::NONE}, target_monster));    
    }
}
}