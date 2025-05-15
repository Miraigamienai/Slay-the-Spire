#include "Game_object/dungeon/Grid_screen_action/Grid_screen_purge_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect_gen/Purge_card_eff_gen.hpp"
#include "Game_object/card/Cards.hpp"

namespace Dungeon{
namespace GridScreenAction{
    void Grid_screen_purge_action::SetCard(const std::shared_ptr<Card::Cards> &card){
        this->is_done=false;
        this->is_cancelled=false;
        this->card=card;
        this->card->SetDrawScale(1.0F, true);
        confirm.show();
        cancel.show();
    }
    
    void Grid_screen_purge_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        confirm.update();
        cancel.update();
        if(cancel.is_logically_clicked()){
            is_cancelled=true;
        }else if(confirm.is_logically_clicked()){
            dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Purge_card_eff_gen>(card));
            dungeon_shared.card_group_handler.erase<Card::GroupType::master_deck>(card);
            is_done=true;
        }
    }

    void Grid_screen_purge_action::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        render_dark_cover(r2);
        render_one_card(r2, card);
        confirm.render(r2);
        cancel.render(r2);
    }
}
}