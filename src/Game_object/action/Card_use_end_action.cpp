#include "Game_object/action/Card_use_end_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect_gen/Exhaust_card_eff_gen.hpp"
#include "Game_object/effect_gen/Empower_circle_gen.hpp"
#include "Game_object/action/Wait_action.hpp"

namespace Action
{
    void Card_use_end_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(duration==0.15F){
            //check where card go
            if(card_item.card->IsExhaust()){
                //the card will not add to flying_cards
                dungeon_shared.card_group_handler.exhaust(card_item.card);
                dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Exhaust_card_eff_gen>(card_item.card));
            }else{
                //cuz the card will add to flying_cards so erase from force render&update early
                dungeon_shared.card_group_handler.erase<Card::GroupType::force_render_cards>(card_item.card);
                dungeon_shared.card_group_handler.erase<Card::GroupType::force_update_cards>(card_item.card);
                if(card_item.card->type==Card::Type::power){
                    dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Wait_action>(0.7F));
                    dungeon_shared.card_group_handler.empower(card_item.card, dungeon_shared.player->GetcX(), dungeon_shared.player->GetcY());
                    dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Empower_circle_gen>(card_item.card, dungeon_shared.player->GetcX(), dungeon_shared.player->GetcY()));
                    //immediately done
                    is_done=true;
                    return;
                }else{
                    dungeon_shared.card_group_handler.discard(card_item.card);//normal case
                }
            }
        }
        TimeGo();
        if(is_done){
            if(card_item.card->IsExhaust()){//only erase when not in flying_cards
                //erases the card that was added by Action_group_handler class. 
                dungeon_shared.card_group_handler.erase<Card::GroupType::force_render_cards>(card_item.card);
                dungeon_shared.card_group_handler.erase<Card::GroupType::force_update_cards>(card_item.card);
            }
        }
    }
} // namespace Action
