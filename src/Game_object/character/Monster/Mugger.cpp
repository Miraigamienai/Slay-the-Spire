#include "Game_object/character/Monster/Mugger.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    Mugger::Mugger(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);

    }
    void Mugger::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(isFirstTwoActions){
            if(ActionCount>=1)
                isFirstTwoActions=false;
            currentAction=Monster::MuggerAction::Mug;
        }
        else if(SmokeBombIsUsed)
            currentAction=Monster::MuggerAction::Escape;
        else
            currentAction=static_cast<Monster::MuggerAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        
        switch(currentAction){
            case Monster::MuggerAction::Mug:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{MUG_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));

                //steal 15 Gold from player.
                break;
            case Monster::MuggerAction::Lunge:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{LUNGE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));

                //steal 15 Gold from player.
                break;
            case Monster::MuggerAction::SmokeBomb:
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
    void Mugger::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
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
    const std::shared_ptr<Draw::ReTexture> &Mugger::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Thieves/Mugger-pretty.png");
    std::discrete_distribution<int> Mugger::dist{ActionProbabilityAfterFirstTwoActions,ActionProbabilityAfterFirstTwoActions+2};
}

