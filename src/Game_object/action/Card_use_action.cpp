#include "Game_object/action/Card_use_action.hpp"//the hpp
#include "Game_object/action/Wait_action.hpp"//wait after power card use
#include "Game_object/card/Cards.hpp"//cards
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Monster_group.hpp"
#include "Game_object/character/Player.hpp"

#include "Util/Logger.hpp"

namespace Action{
    Card_use_action::Card_use_action(const Card::Card_item &card_item, const Monster::Monster_group&room_monsters):
        card_itme(card_item),room_monsters(room_monsters)
    {
        this->duration=0.15F;
    }

    void Card_use_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(this->duration==0.15F){
            //set player move
            if(card_itme.card->type==Card::Type::attack)
                dungeon_shared.player->useFastAttackAnimation();
            
            //use card
            // dungeon_shared.player->ReduceEnergy(card_itme.card->GetCost());
            card_itme.card->Use(dungeon_shared, room_monsters, card_itme.monster);

            //check where card go
            //power type card
            // if(card_itme.card->type==Card::Type::power){
            //     dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Wait_action>(0.7F));
            //     LOG_DEBUG("POWER_CARD_USE");
            //     is_done=true;
            //     return;
            // }
            dungeon_shared.card_group_handler.discard(card_itme.card);
            
        }
        TimeGo();
    }
}