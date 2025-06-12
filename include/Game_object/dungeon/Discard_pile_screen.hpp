#pragma once

#include "Game_object/dungeon/Grid_card_screen.hpp"

//fwd decl
namespace Dungeon{
    struct Dungeon_shared;
}

namespace Dungeon{
class Discard_pile_screen : public Grid_card_screen
{
public:
    Discard_pile_screen():Grid_card_screen(Abstraction::ScreenType::discard_pile){};
    ~Discard_pile_screen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void open(Dungeon::Dungeon_shared &dungeon_shared);
};
}