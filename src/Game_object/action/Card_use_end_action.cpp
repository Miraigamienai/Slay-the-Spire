#include "Game_object/action/Card_use_end_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect_gen/Exhaust_card_eff_gen.hpp"

namespace Action
{
    void Card_use_end_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(duration==0.15F){
            //check where card go
            if(card_item.card->IsExhaust()){
                dungeon_shared.card_group_handler.exhaust(card_item.card);
                dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Exhaust_card_eff_gen>(card_item.card));
            }else{
                dungeon_shared.card_group_handler.discard(card_item.card);//normal case
            }
        }
        TimeGo();
        if(is_done){
            //erases the card that was added by Action_group_handler class. 
            dungeon_shared.card_group_handler.erase<Card::GroupType::force_render_cards>(card_item.card);
            dungeon_shared.card_group_handler.erase<Card::GroupType::force_update_cards>(card_item.card);
        }
    }
} // namespace Action
