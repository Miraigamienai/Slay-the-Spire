#pragma once

#include <vector>
#include <memory>

#include "Game_object/interface/Is_screen.hpp"
#include "Game_object/button/Skip_button.hpp"

//fwd decl
namespace Card{
    class Cards;
}
namespace Dungeon{
    class Dungeon_shared;
}

namespace Dungeon{
class Card_reward_screen final:public Interface::Is_screen
{
public:
    Card_reward_screen();
    ~Card_reward_screen()override=default;

    void Open(const std::vector<std::shared_ptr<Card::Cards>>&cards);
    void update(Dungeon::Dungeon_shared &dungeon_shared);
private:
    Button::Skip_button skip_button;
    std::shared_ptr<Card::Cards> hovered_card;
    std::vector<std::shared_ptr<Card::Cards>> reward_cards;
    void set_cards_pos()const;
};
}
