#include <memory>//shared_ptr

#include "Game_object/card/red/Anger.hpp"//the hpp
#include "Game_object/dungeon/Dungeon_shared.hpp"//for accessing struct members
#include "Game_object/character/Monster/Monsters.hpp"//for passing the monsters to damage action
#include "Game_object/character/Player.hpp"//for passing the player to damage action
#include "Game_object/action/Damage_action.hpp"//for applying damage to the target
#include "Game_object/action/Show_card_to_discard_action.hpp"//show the copy card to discard.
#include "Game_object/Damage_info.hpp"//passes damage parameters
#include "Game_object/action/Effect_gen_capsule_action.hpp"//capsules the Vertical_aura_gen
#include "Game_object/effect_gen/Vertical_aura_gen.hpp"//gen player aura
#include "RUtil/ColorValuesOnly.hpp"//firebrick color

namespace Card{
namespace Red{
    void Anger::Use(Dungeon::Dungeon_shared &dungeon_shared,const Monster::Monster_group &/* room_monsters */,const std::shared_ptr<Monster::Monsters> &target_monster){
        //damage the monster
        dungeon_shared.action_group_handler.AddActionBot(
            std::make_shared<Action::Damage_action>
            (
                Damage_info{this->damage, dungeon_shared.player, AttackType::blunt_heavy},
                target_monster
            )
        );

        //particle to player
        dungeon_shared.action_group_handler.AddActionBot(
            std::make_shared<Action::Effect_gen_capsule_action>(
                std::make_shared<EffectGen::Vertical_aura_gen>(static_cast<Uint32>(RUtil::Colors::FIREBRICK)<<8, dungeon_shared.player->GetX(), dungeon_shared.player->GetY()),
                0.0F
            )
        );
        //show the copy card to discard
        dungeon_shared.action_group_handler.AddActionBot(
            std::make_shared<Action::Show_card_to_discard_action>(
                this->Clone()
            )
        );   
    }
}
}    