#include "Game_object/room/Monster_room.hpp"//the hpp
#include "Game_object/action/Action_group_handler.hpp"//for update
#include "Game_object/card/Card_group_handler.hpp"//for update
#include "Game_object/action/Draw_card_action.hpp"//draw card
#include "Game_object/action/Discard_all_action.hpp"//end turn discard
#include "Game_object/action/Enable_end_button_action.hpp"//controls the time for enabling the end button 
#include "Game_object/dungeon/Overlay.hpp"//combat panel
#include "Game_object/dungeon/Dungeon_shared.hpp"//for update function
#include "Game_object/character/Monster_group_creater.hpp"//create monsters & group_name
#include "RUtil/Image_book.hpp"//for Retexture loading
#include "RUtil/Random_package.hpp"//for passing rng to create monsters
#include "RUtil/Game_Input.hpp"//delta time
#include "Draw/ReTexture.hpp"//IMG Retexture
#include "Draw/Draw_2D.hpp"//for rendering

#include "Util/Logger.hpp"//LOG_ERROR

namespace Room{
Monster_room::Monster_room():Rooms(Room_type::Monster),m_group_name(Monster::GroupName::Jaw_Worm),ending_battle(false),ending_battle_timer(0.25F){
    m_wait_timer=0.0F;
}
void Monster_room::init_room(RUtil::Random_package &random_package,Uint32 dungeon_fade_color){
    Monster::Monster_group_creater::CreateGroup(m_monsters,m_group_name,random_package.monster_type_rng);
    m_wait_timer=0.1F;
}
void Monster_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
    //moster render
    m_monsters.render(r2);
    //player render
}
void Monster_room::update(Dungeon::Dungeon_shared &dungeon_shared){
    if(ending_battle){
        if(ending_battle_timer>0.0F){
            ending_battle_timer-=RUtil::Game_Input::delta_time();
        }else if(this->room_phase==Room_phase::incomplete){
            this->room_phase=Room_phase::just_complete;
        }else{
            this->room_phase=Room_phase::complete;
        }
        return;
    }

    m_monsters.update();
    dungeon_shared.player->update();

    if(m_wait_timer<=0.0F){//Loop until end turn. //Idle also loop here.
        dungeon_shared.action_group_handler.update(dungeon_shared,m_monsters);
        dungeon_shared.card_group_handler.update(dungeon_shared.action_group_handler,m_monsters);
        
        if(dungeon_shared.overlay.end_turn_button_clicked()){
            //ending turn
            //TODO:end logic need to be check.
            dungeon_shared.overlay.disable_end_turn_button();
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Discard_all_action>());
            dungeon_shared.action_group_handler.ending_turn(m_monsters);
            this->m_wait_timer=0.25F;
        }
    }else{
        
        if(dungeon_shared.action_group_handler.is_nothing_to_do()){
            m_wait_timer-=RUtil::Game_Input::delta_time();
        }else{
            dungeon_shared.action_group_handler.update(dungeon_shared,m_monsters);
        }
        if(m_wait_timer<=0.0F){//ready to start turn
            if(/*first*/true){
                //battle start effect
                dungeon_shared.overlay.show_combat_panel();
            }
            dungeon_shared.player->resetEnergy();
            //temporary 5
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Draw_card_action>(5));
        
            //Ensure that enable action will be triggered after the card are drawn.
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Enable_end_button_action>());
            
        }
    }

    //check does battle end
    if(m_monsters.IsAllDie() && dungeon_shared.action_group_handler.is_nothing_to_do()){
        ending_battle=true;
        dungeon_shared.overlay.hide_combat_panel();
        // card_group_handler.on_ending_battle();
        
    }
}

const std::shared_ptr<Draw::ReTexture> &Monster_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monster.png"),
                                       &Monster_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monsterOutline.png");
}