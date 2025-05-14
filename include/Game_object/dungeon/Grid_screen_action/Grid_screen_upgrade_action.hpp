#pragma once

#include "Game_object/dungeon/Grid_screen_action/Grid_screen_action.hpp"
#include "Game_object/dungeon/Grid_screen_action/Render_arrow.hpp"
#include "Game_object/button/Confirm_button.hpp"
#include "Game_object/button/Cancel_button.hpp"

namespace Dungeon{
namespace GridScreenAction{
class Grid_screen_upgrade_action final:public Grid_screen_action,public Render_arrow
{
public:
    Grid_screen_upgrade_action()noexcept(noexcept(Button::Cancel_button{}) && noexcept(Button::Confirm_button{}))
        :Grid_screen_action(true),
        card(nullptr),
        upgraded_card(nullptr){}
    ~Grid_screen_upgrade_action()override=default;
    void SetCard(const std::shared_ptr<Card::Cards> &card)override;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
private:
    Button::Cancel_button cancel;
    Button::Confirm_button confirm;
    std::shared_ptr<Card::Cards> card, upgraded_card;
};
}
}