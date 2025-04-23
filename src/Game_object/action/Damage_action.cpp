#include"Game_object/action/Damage_action.hpp"
namespace Action{
    Damage_action::Damage_action(int num){
        duration=ACTION_DUR_XFAST;
    }
    void Damage_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        TimeGo();
        // if(is_done){
        //     target->damage(num);
        // }
    }
}