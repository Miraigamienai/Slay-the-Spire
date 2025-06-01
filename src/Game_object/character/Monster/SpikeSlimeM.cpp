#include "Game_object/character/Monster/SpikeSlimeM.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    SpikeSlimeM::SpikeSlimeM(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HEIGHT,HPBarWidth
    ,RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Spike Slime/Spike-slime-l-pretty.png"))
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);

    }
    void SpikeSlimeM::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(ActionCount>=2) {
            if(lastAction==Monster::SpikeSlimeMAction::FlameTackle)
                currentAction=Monster::SpikeSlimeMAction::Lick;
            else
                currentAction=Monster::SpikeSlimeMAction::FlameTackle;
        }
        else
            currentAction=static_cast<Monster::SpikeSlimeMAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        switch (currentAction){
            case Monster::SpikeSlimeMAction::FlameTackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{FLAME_TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));


                //shuffles 1 Slimed into the discard pile.
                break;
            case Monster::SpikeSlimeMAction::Lick:
                //	Inflicts 1  Frail.
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

    std::discrete_distribution<int> SpikeSlimeM::dist{ActionProbability,ActionProbability+2};
}

