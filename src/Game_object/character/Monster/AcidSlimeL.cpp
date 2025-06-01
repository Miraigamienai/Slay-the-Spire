#include "Game_object/character/Monster/AcidSlimeL.hpp"
#include "RUtil/Random.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
namespace Monster{
    AcidSlimeL::AcidSlimeL(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HEIGHT,HPBarWidth
        ,RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Acid Slime/Acid-slime-l-pretty.png"))
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);

    }
    void AcidSlimeL::Action(Dungeon::Dungeon_shared &dungeon_shared){
        currentAction=static_cast<Monster::AcidSlimeLAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        if(float(current_HP)/MAX_HP<0.5F){
            currentAction=Monster::AcidSlimeLAction::Split;
        }
        switch (currentAction){
            case Monster::AcidSlimeLAction::CorrosiveSpit:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{CORROSIVE_SPIT_DAMAGE, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));

                // shuffles 2 Slimed into the discard pile.
                break;
            case Monster::AcidSlimeLAction::Lick:
                // Inflict 2  Weak.
                break;
            case Monster::AcidSlimeLAction::Tackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player));
                break;
            case Monster::AcidSlimeLAction::Split:
                // spawn 2 Acid Slime M.
                break;
            default:
                break;
        }
    }

    std::discrete_distribution<int> AcidSlimeL::dist{ActionProbability,ActionProbability+3};
    
}

