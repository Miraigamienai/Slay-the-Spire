#include "Game_object/card/red/Clash.hpp"
#include "Game_object/effect_gen/Clash_eff_gen.hpp"
#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "Game_object/action/Damage_action.hpp"

namespace Card{
namespace Red{
    void Clash::Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster){
        if(!target_monster->IsDie()){
            dungeon_shared.action_group_handler.AddActionBot(
                std::make_shared<Action::Effect_gen_capsule_action>(
                    std::make_shared<EffectGen::Clash_eff_gen>(target_monster->GetcX(), target_monster->GetcY()),
                    0.1F
                )
            );
        }

        dungeon_shared.action_group_handler.AddActionBot(
            std::make_shared<Action::Damage_action>
            (
                Damage_info{this->damage, dungeon_shared.player, AttackType::blunt_heavy},
                target_monster
            )
        );
    }

    bool Clash::CanUse(const Dungeon::Dungeon_shared &dungeon_shared)const{
        return dungeon_shared.card_group_handler.has_all_type_card<Type::attack>();
    }
}
}