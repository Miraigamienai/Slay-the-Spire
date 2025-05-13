#include "Game_object/character/Monster/Cultist.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    Cultist::Cultist(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
        
    }
    void Cultist::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(currentAction==Monster::CultistAction::None || currentAction==Monster::CultistAction::DarkStrike) 
            currentAction=Monster::CultistAction::Incantation;
        else 
            currentAction=Monster::CultistAction::DarkStrike;
        switch (currentAction){
            case Monster::CultistAction::Incantation:
                //Gains 3  Ritual(strength).
                break;
            case Monster::CultistAction::DarkStrike:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{DARK_STRIKE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));
                break;
            default:
                break;
        }
    }
    void Cultist::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
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
    const std::shared_ptr<Draw::ReTexture> &Cultist::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Cultist/Cultist-pretty.png");

}

