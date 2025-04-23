#include "Game_object/action/Empty_shuffle_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Action
{
    void Empty_shuffle_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(first_time){
            first_time=false;
            dungeon_shared.card_group_handler.discard_pile_shuffle_with_rng(dungeon_shared.random_package.card_shuffle_rng);
        }
        duration-=DT;
        while(cnt<amount&&duration<0.0F){
            cnt++;
            duration+=OEN_CARD_SHUFFLE_TIME;
            if(cnt<11)
                dungeon_shared.card_group_handler.shuffle(false);
            else
                dungeon_shared.card_group_handler.shuffle(true);
        }
        if(cnt>=amount)
            is_done=true;
    }    
} // namespace Action
