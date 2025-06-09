#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/button/End_turn_button.hpp"

namespace Action{
//this class only enables the end button. It does nothing else.
//Used to control when the end button should become active.
class Enable_end_button_action final:public Actions
{
public:
    Enable_end_button_action(Button::End_turn_button &button):button(button){};
    ~Enable_end_button_action()override=default;
    void update(Dungeon::Dungeon_shared &/* dungeon_shared */)
        noexcept(noexcept(button.enable())) override
    {
        is_done=true;
        button.enable();
    }
private:
    Button::End_turn_button &button;
};
}
