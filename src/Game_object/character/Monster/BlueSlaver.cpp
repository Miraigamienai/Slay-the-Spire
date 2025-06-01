#include "Game_object/character/Monster/BlueSlaver.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    BlueSlaver::BlueSlaver(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HEIGHT,HPBarWidth,RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Slavers/Slaver-blue-pretty.png"))
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
        
    }
    void BlueSlaver::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(ActionCount>=2) {
            if(lastAction==Monster::BlueSlaverAction::Stab)
                currentAction=Monster::BlueSlaverAction::Rake;
            else
                currentAction=Monster::BlueSlaverAction::Stab;
        }
        else
            currentAction=static_cast<Monster::BlueSlaverAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        switch(currentAction){
            case Monster::BlueSlaverAction::Stab:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{STAB_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));
                break;
            case Monster::BlueSlaverAction::Rake:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{RAKE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));

                //applies 1  Weak.
                break;
            default:
                break;
        }
        if(currentAction!=lastAction){
            ActionCount=1;
            lastAction=currentAction;
        }
        else
            ActionCount++;

    }
    std::discrete_distribution<int> BlueSlaver::dist{ActionProbability,ActionProbability+2};
}

