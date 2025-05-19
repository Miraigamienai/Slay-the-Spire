#include "Game_object/action/Remove_power_action.hpp"
#include "Game_object/character/Characters.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Action{
    void Remove_power_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(duration == ACTION_DUR_XFAST){
            if(target->IsDie()){
                is_done=true;
                return;
            }
            auto &powers=target->get_powers();
            if(powers.contains(power)){
                powers.erase(power);
                dungeon_shared.refresh_display();
            }else{
                is_done=true;
                return;
            }
        }
        
        TimeGo();
    }
}