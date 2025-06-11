#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Flash_attack_effect.hpp"
#include "Game_object/effect/Effect_pool.hpp"
#include "Game_object/Damage_info.hpp"
#include "Game_object/character/Characters.hpp"

namespace Action
{
    Gain_block_action::Gain_block_action(const std::shared_ptr<Character::Characters> &target,int amount):target(target),amount(amount){
        this->duration=0.25F;
    }

    void Gain_block_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(duration==0.25F && !target->IsDie()){
            dungeon_shared.effs.AddTop(Effect::Effect_pool<Effect::Flash_attack_effect>::GetEffect(target->GetcX(), target->GetcY(), AttackType::shield));
            target->AddBlock(this->amount);
        }
        TimeGo();
    }
} // namespace Action
