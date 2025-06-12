#include "Game_object/dungeon/Discard_pile_screen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Dungeon
{
    void Discard_pile_screen::open(Dungeon::Dungeon_shared &dungeon_shared){
        auto&discard=dungeon_shared.card_group_handler.GetCardsGroup<Card::GroupType::m_discard>();
        for(const auto&it:discard){
            it->Lighten(true);
        }
        Grid_card_screen::open(dungeon_shared.card_group_handler.GetCardsGroup<Card::GroupType::m_discard>(), nullptr);
    }

    void Discard_pile_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        Grid_card_screen::update(dungeon_shared);
        if(dungeon_shared.discard_panel.is_logically_clicked() && on_top){
            dungeon_shared.discard_panel.SetClickTimer();
            close();
            dungeon_shared.manager.open<Abstraction::ScreenType::NONE>();
        }
    }
} // namespace Dungeon
