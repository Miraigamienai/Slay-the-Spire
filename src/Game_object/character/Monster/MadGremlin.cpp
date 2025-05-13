#include "Game_object/character/Monster/MadGremlin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    MadGremlin::MadGremlin(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
        m_damage=SCRATCH_DAMAGE;

    }
    void MadGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
            Damage_info{this->m_damage, shared_from_this(), AttackType::blunt_light},
            dungeon_shared.player
        ));
    }
    void MadGremlin::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
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
    void MadGremlin::damage(const Damage_info& damage_info){
        if(current_Block>=damage_info.dmg){
            current_Block-=damage_info.dmg;
            useStaggerAnimation();
            return;
        }
        else if (current_Block){
            current_Block=0;
            current_HP-=damage_info.dmg-current_Block;
        }
        else if (current_HP){
            if(current_HP>damage_info.dmg){
                current_HP-=damage_info.dmg;
            }
            else if (current_HP<=damage_info.dmg){
                current_HP=0;
            }
        }
        m_damage++;
        useStaggerAnimation();
    }
    const std::shared_ptr<Draw::ReTexture> &MadGremlin::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Mad-gremlin-pretty.png");

}

