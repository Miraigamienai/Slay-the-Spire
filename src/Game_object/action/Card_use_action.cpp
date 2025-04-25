#include "Game_object/action/Card_use_action.hpp"//the hpp
#include "Game_object/action/Wait_action.hpp"//wait after power card use
#include "Game_object/card/Cards.hpp"//cards
#include "Game_object/dungeon/Dungeon_shared.hpp"

#include "Util/Logger.hpp"

namespace Action{
    Card_use_action::Card_use_action(const Card::Card_item &card_item, const std::shared_ptr<Character::Characters> &target):
        card_itme(card_item),target(target)
    {
        this->duration=0.15F;
    }

    void Card_use_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(this->duration==0.15F){
            //power type card
            // if(card_itme.card->type==Card::Type::power){
            //     dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Wait_action>(0.7F));
            //     LOG_DEBUG("POWER_CARD_USE");
            //     is_done=true;
            //     return;
            // }
            // card_group_handler.discard(m_card_itme.card);
            
        }
        TimeGo();
    }
}