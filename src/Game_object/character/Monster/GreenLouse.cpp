#include "Game_object/character/Monster/GreenLouse.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    GreenLouse::GreenLouse(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth
    ,RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Louses/Louse-green-pretty.png"))
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
        m_damage=RUtil::Random::GetRandomInt(MAX_DAMAGE-MIN_DAMAGE)+MIN_DAMAGE;

    }
    void GreenLouse::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(ActionCount>=2) {
            if(lastAction==Monster::GreenLouseAction::Bite)
                currentAction=Monster::GreenLouseAction::SpitWeb;
            else
                currentAction=Monster::GreenLouseAction::Bite;
        }
        else
            currentAction=static_cast<Monster::GreenLouseAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        switch (currentAction){
            case Monster::GreenLouseAction::Bite:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{this->m_damage, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));
                break;
            case Monster::GreenLouseAction::SpitWeb:
                //	Applies 2  Weak.
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

    std::discrete_distribution<int> GreenLouse::dist{ActionProbability,ActionProbability+2};
}

