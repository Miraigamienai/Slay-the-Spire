#pragma once

#include <deque>

#include "Game_object/card/Card_item.hpp"//Card queue
#include "Game_object/action/Action_group.hpp"//member
#include "Game_object/character/Monster_group.hpp"//for add monsters to queue

//fwd decl
namespace Monster{
    class Monsters;
}
namespace Dungeon{
    struct Dungeon_shared;
}
namespace Card{
    class Card_group_handler;
}

namespace Action{
class Action_group_handler
{
public:
    Action_group_handler()=default;
    ~Action_group_handler()=default;
    Action_group_handler(const Action_group_handler &) = delete;
    Action_group_handler(Action_group_handler &&) = delete;
    Action_group_handler &operator=(const Action_group_handler &) = delete;
    Action_group_handler &operator=(Action_group_handler &&)=delete;
    
    void update(Dungeon::Dungeon_shared &dungeon_shared, const Monster::Monster_group&room_monsters);
    bool is_nothing_to_do()const{return this->current_action==nullptr&&action_box.empty();}
    void prepare_for_battle();
    //need the monsters so they can take there turn.
    void ending_turn(const Monster::Monster_group&room_monsters){
        for(const auto &it:room_monsters){
            monster_queue.emplace_back(it);
        }
        is_endding_turn=true;
    }

    void AddActionTop(std::shared_ptr<Actions>&&action){action_box.AddTop(std::move(action));}
    void AddActionBot(std::shared_ptr<Actions>&&action){action_box.AddBot(std::move(action));}
    void AddActionTop(const std::shared_ptr<Actions>&action){action_box.AddTop(action);}
    void AddActionBot(const std::shared_ptr<Actions>&action){action_box.AddBot(action);}
    void AddCardQueue(Card::Card_item &&card_item){card_queue.emplace_back(std::move(card_item));}
    void AddCardQueue(const Card::Card_item &card_item){card_queue.emplace_back(card_item);}
private:
    void get_next_action(Dungeon::Dungeon_shared &dungeon_shared,const Monster::Monster_group&room_monsters);
    Action_group action_box,pre_action_box;
    std::deque<Card::Card_item> card_queue;
    std::vector<std::shared_ptr<Monster::Monsters>> monster_queue;
    bool is_wating_player=false;
    bool is_endding_turn=false;
    std::shared_ptr<Actions> current_action;
};
}