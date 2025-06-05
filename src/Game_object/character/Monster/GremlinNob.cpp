#include "Game_object/character/Monster/GremlinNob.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    GremlinNob::GremlinNob(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth
    ,RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlin Nob/Gremlin-nob-pretty.png"))
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
    }
    void GremlinNob::Action(Dungeon::Dungeon_shared &dungeon_shared){
        do {
            currentAction=static_cast<Monster::GremlinNobAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        } while (
            (currentAction == lastAction && ActionCount >= 1 && currentAction != Monster::GremlinNobAction::Thrash) ||
            (currentAction == Monster::GremlinNobAction::Thrash && lastAction == Monster::GremlinNobAction::Thrash && ActionCount >= 2)
        );
        switch (currentAction){
            case Monster::GremlinNobAction::Chomp:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{CHOMP_DAMAGE, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));
                break;
            case Monster::GremlinNobAction::Thrash:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{THRASH_DAMAGE, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));

                
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), THRASH_BLOCK));
                break;

            case Monster::GremlinNobAction::Bellow:
                // Gain 3  Strength

                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), BELLOWS_BLOCK));
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

    std::discrete_distribution<int> GremlinNob::dist{ActionProbability,ActionProbability+3};
}

