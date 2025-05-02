#include "Game_object/character/Monster/FatGremlin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    FatGremlin::FatGremlin():Monsters(Setting::WINDOW_WIDTH*0.5F+WIDTH_OFFSET,Setting::WINDOW_HEIGHT*0.5F+HEIGHT_OFFSET, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(40,44);
        setBlock(0);
        m_damage=12;
        setPosition(Setting::WINDOW_WIDTH*0.5F+WIDTH_OFFSET,Setting::WINDOW_HEIGHT*0.5F+HEIGHT_OFFSET);
        setHPBarWidth(WIDTH*0.8F);
    }
    
    void FatGremlin::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        r2->SetColor(-1);
        r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT); 
        render_HP(r2);
    }

    void FatGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
            Damage_info{this->m_damage, shared_from_this(), AttackType::blunt_light},
            dungeon_shared.player
        ));
    }

    const std::shared_ptr<Draw::ReTexture> &FatGremlin::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Fat-gremlin-pretty.png");

}

