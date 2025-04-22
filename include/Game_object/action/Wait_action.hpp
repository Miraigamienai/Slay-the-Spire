#pragma once

#include "Game_object/action/Actions.hpp"

namespace Action{
class Wait_action final:public Actions
{
public:
    Wait_action(float dur)noexcept{this->duration=dur;}
    ~Wait_action()override=default;
    void update(Card::Card_group_handler &/* card_group_handler */,Action_group_handler &/* action_group_handler */,const RUtil::Random_package &/* random_package */)
        noexcept(noexcept(TimeGo())) override  
    {
        TimeGo();
    }

};
}