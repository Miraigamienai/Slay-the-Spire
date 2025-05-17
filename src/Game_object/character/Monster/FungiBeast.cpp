#include "Game_object/character/Monster/FungiBeast.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    FungiBeast::FungiBeast(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
    }
    void FungiBeast::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(lastAction==Monster::FungiBeastAction::Bite && ActionCount>=2)
            currentAction=Monster::FungiBeastAction::Grow;
        else if(lastAction==Monster::FungiBeastAction::Grow)
            currentAction=Monster::FungiBeastAction::Bite;
        else{
                currentAction=static_cast<Monster::FungiBeastAction>(dist(dungeon_shared.random_package.monster_ai_rng));
                switch (currentAction){
                case Monster::FungiBeastAction::Bite:
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{BITE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player));
                    break;
                case Monster::FungiBeastAction::Grow:
                    //Gain 3  Strength.
                    break;


                default:
                    break;
            }
        }

        if(currentAction!=lastAction){
            ActionCount=1;
            lastAction=currentAction;
        }
        else
            ActionCount++;
    }
    void FungiBeast::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
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
    const std::shared_ptr<Draw::ReTexture> &FungiBeast::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Fungi Beast/Fungi-beast-pretty.png");
    std::discrete_distribution<int> FungiBeast::dist{ActionProbability,ActionProbability+2};
}

