#include "Game_object/action/Action_group_handler.hpp"//the hpp
#include "Game_object/action/Card_use_start_action.hpp"//use card
#include "Game_object/action/Wait_action.hpp"//for wait
#include "Game_object/character/Monster/Monsters.hpp"//monster take turn
#include "Game_object/dungeon/Dungeon_shared.hpp"//for update function

#include "Util/Logger.hpp"

namespace Action
{
    void Action_group_handler::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(is_wating_player){
            get_next_action(dungeon_shared);
        }else{
            if(current_action!=nullptr){
                current_action->update(dungeon_shared);
                if(current_action->IsDone()) current_action=nullptr;
            }else{
                get_next_action(dungeon_shared);
                if(current_action==nullptr){
                    dungeon_shared.card_group_handler.refresh_hand_layout();
                    is_wating_player=true;
                }
            }
        }
    }
    void Action_group_handler::get_next_action(Dungeon::Dungeon_shared &dungeon_shared){
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
            if((card_queue.front().card->IsSingleTarget()&&card_queue.front().monster->IsDie())|| dungeon_shared.room_monsters.IsAllDie()){
                //can't play //add some logic later
                
            }else{
                //can play
                //removes card from hand
                dungeon_shared.card_group_handler.erase<Card::GroupType::hand_cards>(card_queue.front().card);
                //adds the card to the force_render_cards and force_update_cards .It will be removed when Card_use_end_action finishes.
                dungeon_shared.card_group_handler.AddTop<Card::GroupType::force_render_cards>(card_queue.front().card);
                dungeon_shared.card_group_handler.AddTop<Card::GroupType::force_update_cards>(card_queue.front().card);
                //use the card
                card_queue.front().card->SetX((float)Setting::WINDOW_WIDTH/2.0F);
                card_queue.front().card->SetY((float)Setting::WINDOW_HEIGHT/2.0F);
                card_queue.front().card->SetAngle(0.0F, true);
                action_box.AddBot(std::make_shared<Card_use_start_action>(card_queue.front()));
            }
            card_queue.pop_front();
        }else if(!monster_queue.empty()){
            monster_queue.back()->Action(dungeon_shared);
            //TODO: intent update
            monster_queue.pop_back();
            if(monster_queue.empty())
                action_box.AddBot(std::make_shared<Wait_action>(1.0F));//wait after monster turn end.
        }else if(is_endding_turn){
            is_endding_turn=false;
            dungeon_shared.player->at_turn_end(dungeon_shared);
            dungeon_shared.room_monsters.at_turn_end(dungeon_shared);
            //player turn start
            dungeon_shared.player->at_turn_start(dungeon_shared);
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
