#include "Game_object/action/Action_group_handler.hpp"//the hpp
#include "Game_object/action/Card_use_action.hpp"//use card
#include "Game_object/action/Wait_action.hpp"//for wait
#include "Game_object/character/Monster/Monsters.hpp"//monster take turn
#include "Game_object/dungeon/Dungeon_shared.hpp"//for update function

#include "Util/Logger.hpp"

namespace Action
{
    void Action_group_handler::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(is_wating_player){
            get_next_action();
        }else{
            if(current_action!=nullptr){
                current_action->update(dungeon_shared);
                if(current_action->IsDone()) current_action=nullptr;
            }else{
                get_next_action();
                if(current_action==nullptr){
                    dungeon_shared.card_group_handler.refresh_hand_layout();
                    is_wating_player=true;
                }
            }
        }
    }
    void Action_group_handler::get_next_action(){
        if(!action_box.empty()){
            current_action=action_box.PopTop();
            is_wating_player=false;
        }else if(!pre_action_box.empty()){
            current_action=pre_action_box.PopTop();
            is_wating_player=false;
        }else if(!card_queue.empty()){//Using Bot(front) card
            //remember check if card can't use
            // action_box.AddBot(std::make_shared<Card_use_action>(card_queue.front()));
            card_queue.front().card->SetX((float)Setting::WINDOW_WIDTH/2.0F);
            card_queue.front().card->SetY((float)Setting::WINDOW_HEIGHT/2.0F);
            //reduce energy
            card_queue.pop_front();
        }else if(!monster_queue.empty()){

            monster_queue.pop_back();
        }else if(is_endding_turn){
            is_endding_turn=false;
            action_box.AddBot(std::make_shared<Wait_action>(1.5F));//wait after monster turn end.

        }
    }

    void Action_group_handler::prepare_for_battle(){
        if(!action_box.empty()){
            LOG_ERROR("There are some remain action in box.");
            action_box.Clear();
        }
        action_box.AddTop(std::make_shared<Action::Wait_action>(1.0F));
    }
    
} // namespace Action
