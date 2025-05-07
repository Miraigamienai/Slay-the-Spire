#include "Game_object/dungeon/Grid_screen_action/Grid_screen_upgrade_action.hpp"
#include "Game_object/card/Cards.hpp"

namespace Dungeon{
namespace GridScreenAction{
    Grid_screen_upgrade_action::Grid_screen_upgrade_action():card(nullptr),upgraded_card(nullptr){
    }

    void Grid_screen_upgrade_action::SetCard(const std::shared_ptr<Card::Cards> &card){
        this->is_cancelled=false;
        this->card=card;
        this->upgraded_card=card->Clone();
        this->upgraded_card->Upgrade();
        confirm.show();
        cancel.show();
    }
    
    void Grid_screen_upgrade_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        arrow_update();
        confirm.update();
        cancel.update();
        if(cancel.is_logically_clicked()){
            is_cancelled=true;
        }else if(confirm.is_logically_clicked()){
            card->Upgrade();
            is_done=true;
        }
    }

    void Grid_screen_upgrade_action::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        render_dark_cover(r2);
        arrow_render(r2);
        render_two_card(r2, card, upgraded_card);
        confirm.render(r2);
        cancel.render(r2);
    }
}
}