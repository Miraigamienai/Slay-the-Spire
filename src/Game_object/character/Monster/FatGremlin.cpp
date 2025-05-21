#include "Game_object/character/Monster/FatGremlin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    FatGremlin::FatGremlin(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth
    ,RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Fat-gremlin-pretty.png"))
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
    }
    void FatGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
            Damage_info{SMASH_DAMAGE, shared_from_this(), AttackType::blunt_light},
            dungeon_shared.player
        ));
        
        //apply 1  Weak.
    }

}

