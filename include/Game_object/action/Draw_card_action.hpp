#pragma once

#include "Game_object/action/Actions.hpp"

namespace Action{
class Draw_card_action final:public Actions
{
public:
    Draw_card_action(int amount)noexcept:first_time(true),amount(amount){
        this->duration=ACTION_DUR_FASTER;
    }
    ~Draw_card_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    bool first_time;
    int amount;
};
}