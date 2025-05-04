#pragma once

#include <vector>
#include <memory>

#include "Game_object/button/Skip_button.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
}
namespace Card{
    class Cards;
}
namespace Dungeon{
    class Dungeon_shared;
}

namespace Reward{
class Card_reward
{
public:
    Card_reward(const std::vector<std::shared_ptr<Card::Cards>>&cards);
    ~Card_reward()=default;

    void Open();
    void update(Dungeon::Dungeon_shared &dungeon_shared);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 PlayerColor_RGB)const;
    bool IsChosen()const noexcept{return chosen;}
    bool SkipButtonClicked()const noexcept(noexcept(skip_button.is_logically_clicked())){return skip_button.is_logically_clicked();}
private:
    Button::Skip_button skip_button;
    bool chosen;
    std::shared_ptr<Card::Cards> hovered_card;
    std::vector<std::shared_ptr<Card::Cards>> reward_cards;
    void set_cards_pos()const;
};
}
