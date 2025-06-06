#include "Game_object/action/Random_monster_gain_block.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Effect_pool.hpp"
#include "Game_object/effect/Flash_attack_effect.hpp"
#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/Damage_info.hpp"

namespace Action{
    Random_monster_gain_block::Random_monster_gain_block(const std::shared_ptr<Character::Characters> &src, int amt)
        :src(src), amt(amt)
    {
        duration=DUR;
    }
    void Random_monster_gain_block::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(duration==DUR){
            std::shared_ptr<Character::Characters> target=nullptr;
            std::vector<std::shared_ptr<Monster::Monsters>> can_add_monsters;
            for(const auto&it:dungeon_shared.room_monsters)
                if(!it->IsDie() && it!=src && it->GetIntent()!=Monster::Intent::escape)
                    can_add_monsters.emplace_back(it);
            if(can_add_monsters.empty()) target=src;
            else target=can_add_monsters[dungeon_shared.random_package.monster_ai_rng.NextInt(static_cast<int>(can_add_monsters.size()))];
            
            if(target!=nullptr){
                dungeon_shared.effs.AddTop(Effect::Effect_pool<Effect::Flash_attack_effect>::GetEffect(target->GetcX(), target->GetcY(), AttackType::shield));
                target->AddBlock(amt);
            }
        }
        TimeGo();
    }
}