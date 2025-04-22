#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/dungeon/Overlay.hpp"

namespace Action{
//this class only enables the end button. It does nothing else.
//Used to control when the end button should become active.
class Enable_end_button_action final:public Actions
{
public:
    Enable_end_button_action(Dungeon::Overlay &overlay):overlay(overlay){};
    ~Enable_end_button_action()override=default;
    void update(Card::Card_group_handler &/*card_group_handler*/,Action_group_handler &/*action_group_handler*/,const RUtil::Random_package &/*random_package*/)
        noexcept(noexcept(overlay.enable_end_turn_button())) override
    {
        is_done=true;
        overlay.enable_end_turn_button();
    }
private:
    Dungeon::Overlay &overlay;
};
}
