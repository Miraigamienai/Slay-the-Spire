#include "Game_object/character/Monster/RedSlaver.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    RedSlaver::RedSlaver(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
        
    }
    void RedSlaver::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(isFirstAction){
            isFirstAction=false;
            currentAction=Monster::RedSlaverAction::Stab;
        }
        else if(EntangleIsUsed)
            if(ActionCount>=2) 
                if(lastAction==Monster::RedSlaverAction::Scrape)
                    currentAction=Monster::RedSlaverAction::Stab;
                else
                    currentAction=Monster::RedSlaverAction::Scrape;
            else
                currentAction=static_cast<Monster::RedSlaverAction>(dungeon_shared.random_package.monster_ai_rng.GetRandomWithWeight(ActionProbabilityAfterEntangle,sizeof(ActionProbabilityAfterEntangle)/sizeof(float)));
        
        else if(lastAction==Monster::RedSlaverAction::Stab) 
            currentAction=Monster::RedSlaverAction::Scrape;
        
        else if(lastAction==Monster::RedSlaverAction::Scrape && ActionCount>=2) 
            currentAction=Monster::RedSlaverAction::Stab;
        else
            currentAction=Monster::RedSlaverAction::Scrape;

        switch(currentAction){
            case Monster::RedSlaverAction::Stab:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{STAB_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));
                break;
            case Monster::RedSlaverAction::Scrape:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{SCRAPE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));
                break;
            case Monster::RedSlaverAction::Entangle:
                EntangleIsUsed=true;

                //Applies 1  Entangled(You may not play any Attacks this turn.).
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
    void RedSlaver::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
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
    const std::shared_ptr<Draw::ReTexture> &RedSlaver::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Slavers/Slaver-red-pretty.png");

}

