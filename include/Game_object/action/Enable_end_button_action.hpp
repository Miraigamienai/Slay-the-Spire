#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/dungeon/Overlay.hpp"

namespace Action{
//this class only enables the end button. It does nothing else.
//Used to control when the end button should become active.
class Enable_end_button_action final:public Actions
{
public:
    Enable_end_button_action()=default;
    ~Enable_end_button_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)
        noexcept(noexcept(dungeon_shared.overlay.enable_end_turn_button())) override
    {
        is_done=true;
        dungeon_shared.overlay.enable_end_turn_button();
    }
};
}
