#include "Game_object/action/Damage_action.hpp"
#include "Game_object/effect/Effect_pool.hpp"//reuse eff
#include "Game_object/effect/Flash_attack_effect.hpp"//eff
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Characters.hpp"//target
#include "Game_object/action/Wait_action.hpp"//wait 0.1F
#include "Game_object/Damage_info.hpp"

namespace Action{
    Damage_action::Damage_action(const Damage_info&damage_info,const std::shared_ptr<Character::Characters> &target, bool deduct_block)
        :damage_info(damage_info), target(target), deduct_block(deduct_block)
    {
        duration=ACTION_DUR_XFAST;
    }
    void Damage_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        //remember do thorn
        if(this->duration==ACTION_DUR_XFAST){
            if(target->IsDie()) this->is_done=true;
            else if(damage_info.attack_type != AttackType::NONE){
                dungeon_shared.effs.AddTop(Effect::Effect_pool<Effect::Flash_attack_effect>::GetEffect(target->GetcX(),target->GetcY(),damage_info.attack_type));
            }
        }
        TimeGo();
        if(is_done){
            //damage the target 
            target->damage(this->damage_info, dungeon_shared, deduct_block);
            dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Wait_action>(0.1F));
        }
    }
}