#pragma once

#include "Game_object/action/Actions.hpp"

namespace Action{
class Discard_all_action final:public Actions
{
public:
    Discard_all_action()noexcept{
        duration=ACTION_DUR_XFAST;
    }
    ~Discard_all_action()override=default;
    void update(Card::Card_group_handler &card_group_handler,Action_group_handler &/* action_group_handler */,const RUtil::Random_package &/* random_package */)override{
        if(duration==ACTION_DUR_XFAST)
            card_group_handler.discard_all();
        TimeGo();   
    }
};
}