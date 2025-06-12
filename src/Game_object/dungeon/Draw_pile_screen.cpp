#include "Game_object/dungeon/Draw_pile_screen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Dungeon
{
    void Draw_pile_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        Grid_card_screen::update(dungeon_shared);
        if(dungeon_shared.draw_panel.is_logically_clicked() && on_top){
            dungeon_shared.draw_panel.SetClickTimer();
            close();
            dungeon_shared.manager.open<Abstraction::ScreenType::NONE>();
        }
    }

    void Draw_pile_screen::open(Dungeon::Dungeon_shared &dungeon_shared){
        Card::Card_group draw_copy;
        draw_copy.CloneOther(dungeon_shared.card_group_handler.GetCardsGroup<Card::GroupType::draw_pile>());
        draw_copy.SortByRarity(true);
        Grid_card_screen::open(std::move(draw_copy), nullptr);
    }
}