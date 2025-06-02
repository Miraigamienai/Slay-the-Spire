#include "Game_object/action/Card_use_start_action.hpp"//the hpp
#include "Game_object/action/Wait_action.hpp"//wait after power card use
#include "Game_object/action/Card_use_end_action.hpp"
#include "Game_object/card/Cards.hpp"//cards
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Player.hpp"

#include "Util/Logger.hpp"

namespace Action{
    Card_use_start_action::Card_use_start_action(const Card::Card_item &card_item):
        card_item(card_item){}

    void Card_use_start_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        //set player move
        if(card_item.card->type==Card::Type::attack)
            dungeon_shared.player->use_animation<Character::Animation::ATTACK_FAST>();
        
        //use card
        dungeon_shared.player->ReduceEnergy(card_item.card->GetCost(),dungeon_shared);
        card_item.card->Use(dungeon_shared, card_item.monster);
        
        //add end to bot
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Card_use_end_action>(card_item));
        
        //done immediately
        this->is_done=true;
    }
}