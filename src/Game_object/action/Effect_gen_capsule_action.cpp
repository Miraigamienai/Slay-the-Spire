#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Action
{
    void Effect_gen_capsule_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(duration==start_dur&& eff_gen!=nullptr){
            dungeon_shared.gen_group.AddTop(eff_gen);
        }
        TimeGo();
    }
} // namespace Action
