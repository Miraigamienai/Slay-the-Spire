#include "Game_object/action/Discard_all_action.hpp"
namespace Action
{
    Discard_all_action::Discard_all_action(){
        duration=ACTION_DUR_XFAST;
    }
    void Discard_all_action::update(Card::Card_group_handler &card_group_handler,Action_group_handler*const action_group_handler,const RUtil::Random_package &random_package){
        if(duration==ACTION_DUR_XFAST)
            card_group_handler.discard_all();
        TimeGo();
    }
} // namespace Action
