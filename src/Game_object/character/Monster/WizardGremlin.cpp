#include "Game_object/character/Monster/WizardGremlin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    WizardGremlin::WizardGremlin(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth
    ,RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Wizard-gremlin-pretty.png"))
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);

    }
    void WizardGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if((isFirstAttack && ChargingCounter>=2) || ChargingCounter>=3){
            isFirstAttack=false;
            ChargingCounter=0;
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{ULTIMATE_BLAST, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player
            ));
        }
        else 
            ChargingCounter++;
        

    }

}

