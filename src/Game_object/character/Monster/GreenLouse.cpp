#include "Game_object/character/Monster/GreenLouse.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    GreenLouse::GreenLouse(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
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
            currentAction=static_cast<Monster::GreenLouseAction>(dungeon_shared.random_package.monster_ai_rng.GetRandomWithWeight(ActionProbability,sizeof(ActionProbability)/sizeof(float)));
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
    void GreenLouse::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
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
    const std::shared_ptr<Draw::ReTexture> &GreenLouse::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Louses/Louse-green-pretty.png");

}

