#include "Game_object/character/Monster/Looter.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    Looter::Looter(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth
    ,RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Thieves/Looter-pretty.png"))
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);

    }
    void Looter::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(isFirstTwoActions){
            if(ActionCount>=1)
                isFirstTwoActions=false;
            currentAction=Monster::LooterAction::Mug;
        }
        else if(SmokeBombIsUsed)
            currentAction=Monster::LooterAction::Escape;
        else
            currentAction=static_cast<Monster::LooterAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        
        switch(currentAction){
            case Monster::LooterAction::Mug:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{MUG_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));

                //steal 15 Gold from player.
                break;
            case Monster::LooterAction::Lunge:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{LUNGE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));

                //steal 15 Gold from player.
                break;
            case Monster::LooterAction::SmokeBomb:
                SmokeBombIsUsed=true;
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), SMOKE_BOMB_BLOCK));
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

    std::discrete_distribution<int> Looter::dist{ActionProbabilityAfterFirstTwoActions,ActionProbabilityAfterFirstTwoActions+2};
}

