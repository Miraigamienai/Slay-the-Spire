#include "Game_object/character/Monster/ShieldGremlin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    ShieldGremlin::ShieldGremlin(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);

    }
    void ShieldGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        //if there has at least 1 monster, randomly choose one to add block on it.


        
        //if there is no monster, attack on player.
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
            Damage_info{SHIELD_BASH_DAMAGE, shared_from_this(), AttackType::blunt_light},
            dungeon_shared.player
        ));
    }
    void ShieldGremlin::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
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
    const std::shared_ptr<Draw::ReTexture> &ShieldGremlin::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Shield-Gremlin-pretty.png");

}

