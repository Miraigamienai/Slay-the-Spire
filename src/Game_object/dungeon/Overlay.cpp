#include "Game_object/dungeon/Overlay.hpp"
namespace Dungeon{
    void Overlay::update(const Card::Card_group_handler &card_group_handler){
        energy_panel.update();
        end_turn_button.update(card_group_handler);
    }
    void Overlay::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        energy_panel.render(r2);
        end_turn_button.render(r2);
    }
    void Overlay::hide_combat_panel(){
        energy_panel.hide();
        end_turn_button.hide();
    };
    void Overlay::show_combat_panel(){
        energy_panel.show();
        end_turn_button.show();
    };
    
}