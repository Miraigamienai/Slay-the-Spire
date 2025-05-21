#include "Game_object/action/Reduce_power_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Remove_power_action.hpp"
#include "Game_object/character/Characters.hpp"

namespace Action{
    void Reduce_power_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(this->duration==ACTION_DUR_FAST){//first in
            const int power_amt=power->get_amount();
            if(amount==power_amt || power_amt==0){
                dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Remove_power_action>(power, target));
                is_done=true;
                return;
            }else if(amount < power_amt){
                power->reduce_amount(amount);
                power->desc_update();
                dungeon_shared.refresh_display();
            }
        }
        TimeGo();
    }
}