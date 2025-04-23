#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Action{
class Discard_all_action final:public Actions
{
public:
    Discard_all_action()noexcept{
        duration=ACTION_DUR_XFAST;
    }
    ~Discard_all_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(duration==ACTION_DUR_XFAST)
            dungeon_shared.card_group_handler.discard_all();
        TimeGo();   
    }
};
}