#include "Game_object/character/Monster/JawWorm.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "RUtil/Random.hpp"
#include <iostream>
namespace Monster{
    JawWorm::JawWorm(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
    }
    void JawWorm::Action(Dungeon::Dungeon_shared &dungeon_shared){
        do {
            currentAction = static_cast<Monster::JawWormAction>(
                dungeon_shared.random_package.monster_ai_rng.GetRandomWithWeight(
                    ActionProbability,
                    sizeof(ActionProbability) / sizeof(float)
                )
            );
        } while (
            (currentAction == lastAction && ActionCount >= 1 && currentAction != Monster::JawWormAction::Thrash) ||
            (currentAction == Monster::JawWormAction::Thrash && lastAction == Monster::JawWormAction::Thrash && ActionCount >= 2)
        );
        switch (currentAction){
            case Monster::JawWormAction::Chomp:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{CHOMP_DAMAGE, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));
                break;
            case Monster::JawWormAction::Thrash:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{THRASH_DAMAGE, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));

                
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), THRASH_BLOCK));
                break;

            case Monster::JawWormAction::Bellow:
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
    void JawWorm::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        if(IsFadeOut){
            r2->SetColor(-1,FadeColorA);
            r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT); 
        }
        else{
            r2->SetColor(-1);
            r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT); 
            render_HP(r2);
        }

    }
    const std::shared_ptr<Draw::ReTexture> &JawWorm::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Jaw Worm/Jaw-worm-pretty.png");
    
}

