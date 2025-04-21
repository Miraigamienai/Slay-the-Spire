#include "Game_object/room/Monster_room.hpp"//the hpp
#include "Game_object/action/Action_group_handler.hpp"//for update
#include "Game_object/card/Card_group_handler.hpp"//for update
#include "Game_object/action/Draw_card_action.hpp"//draw card
#include "Game_object/dungeon/Overlay.hpp"//combat panel
#include "Game_object/character/Monster_group_creater.hpp"//create monsters & group_name
#include "RUtil/Image_book.hpp"//for Retexture loading
#include "RUtil/Random_package.hpp"//for passing rng to create monsters
#include "Draw/ReTexture.hpp"//IMG Retexture
#include "Draw/Draw_2D.hpp"//for rendering

#include "Util/Logger.hpp"//LOG_ERROR
#include "Util/Input.hpp"//for test

namespace Room{
Monster_room::Monster_room():Rooms(Room_type::Monster),m_group_name(Monster::GroupName::None){
    m_wait_timer=0.0F;
}
void Monster_room::init_room(RUtil::Random_package &random_package){
    Monster::Monster_group_creater::CreateGroup(m_monsters,m_group_name,random_package.monster_type_rng);
    m_wait_timer=0.1F;
}
void Monster_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
    //moster render
    m_monsters.render(r2);
    //player render
}
void Monster_room::update(Action::Action_group_handler &action_group_handler,Card::Card_group_handler &card_group_handler,Dungeon::Overlay &overlay,const RUtil::Random_package &random_package){
    m_monsters.update();
    
    if(m_wait_timer<=0.0F){//Loop until end turn. //Idle also loop here.
        action_group_handler.update(card_group_handler,random_package);
        card_group_handler.update(action_group_handler,m_monsters);
        
        if(Util::Input::IsKeyDown(Util::Keycode::A)){//for test
            action_group_handler.AddActionTop(std::make_shared<Action::Draw_card_action>(5));
        }
        if(Util::Input::IsKeyDown(Util::Keycode::S)){//for test
            card_group_handler.discard_all();
        }
    }else{
        if(action_group_handler.is_nothing_to_do()){
            m_wait_timer-=RUtil::Game_Input::delta_time();
        }else{
            action_group_handler.update(card_group_handler,random_package);
        }
        if(m_wait_timer<=0.0F){//ready to start turn
            if(/*first*/true){
                //battle start effect
                overlay.show_combat_panel();
            }
            //energy
            action_group_handler.AddActionBot(std::make_shared<Action::Draw_card_action>(5));//temporary 5
            overlay.enable_end_turn_button();
            
            //panel?
        }
    }
}

const std::shared_ptr<Draw::ReTexture> &Monster_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monster.png"),
                                       &Monster_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monsterOutline.png");
}