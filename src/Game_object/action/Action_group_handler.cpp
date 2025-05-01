#include "Game_object/action/Action_group_handler.hpp"//the hpp
#include "Game_object/action/Card_use_start_action.hpp"//use card
#include "Game_object/action/Wait_action.hpp"//for wait
#include "Game_object/character/Monster/Monsters.hpp"//monster take turn
#include "Game_object/dungeon/Dungeon_shared.hpp"//for update function

#include "Util/Logger.hpp"

namespace Action
{
    void Action_group_handler::update(Dungeon::Dungeon_shared &dungeon_shared, const Monster::Monster_group&room_monsters){
        if(is_wating_player){
            get_next_action(room_monsters, dungeon_shared.card_group_handler);
        }else{
            if(current_action!=nullptr){
                current_action->update(dungeon_shared);
                if(current_action->IsDone()) current_action=nullptr;
            }else{
                get_next_action(room_monsters, dungeon_shared.card_group_handler);
                if(current_action==nullptr){
                    //TODO:This part still needs to be verified.
                    // dungeon_shared.card_group_handler.refresh_hand_layout();
                    is_wating_player=true;
                }
            }
        }
    }
    void Action_group_handler::get_next_action(const Monster::Monster_group&room_monsters, Card::Card_group_handler &card_group_handler){
        if(!action_box.empty()){
            current_action=action_box.PopTop();
            is_wating_player=false;
        }else if(!pre_action_box.empty()){
            current_action=pre_action_box.PopTop();
            is_wating_player=false;
        }else if(!card_queue.empty()){//Using Bot(front) card
            //let the card can be hovered.
            card_queue.front().card->SetCanHoverInHand(true);
            //check if card playable
            if((card_queue.front().card->IsSingleTarget()&&card_queue.front().monster->IsDie())|| room_monsters.IsAllDie()){
                //can't play //add some logic later
                
            }else{
                //can play
                //removes card from hand
                card_group_handler.erase<Card::GroupType::hand_cards>(card_queue.front().card);
                //adds the card to the force_render_cards and force_update_cards .It will be removed when Card_use_end_action finishes.
                card_group_handler.AddTop<Card::GroupType::force_render_cards>(card_queue.front().card);
                card_group_handler.AddTop<Card::GroupType::force_update_cards>(card_queue.front().card);
                //use the card
                action_box.AddBot(std::make_shared<Card_use_start_action>(card_queue.front(),room_monsters));
                card_queue.front().card->SetX((float)Setting::WINDOW_WIDTH/2.0F);
                card_queue.front().card->SetY((float)Setting::WINDOW_HEIGHT/2.0F);
            }
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
            action_box.clear();
        }
        action_box.AddTop(std::make_shared<Action::Wait_action>(1.0F));
    }
    
} // namespace Action
