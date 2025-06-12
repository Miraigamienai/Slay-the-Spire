#pragma once

#include "Game_object/dungeon/Grid_card_screen.hpp"

//fwd decl
namespace Dungeon{
    struct Dungeon_shared;
}

namespace Dungeon{
class Draw_pile_screen : public Grid_card_screen
{
public:
    Draw_pile_screen():Grid_card_screen(Abstraction::ScreenType::draw_pile){};
    ~Draw_pile_screen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void open(Dungeon::Dungeon_shared &dungeon_shared);
};
}