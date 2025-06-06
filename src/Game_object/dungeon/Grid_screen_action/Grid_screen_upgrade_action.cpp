#include "Game_object/dungeon/Grid_screen_action/Grid_screen_upgrade_action.hpp"
#include "Game_object/effect_gen/Card_upgrade_eff_gen.hpp"
#include "Game_object/effect_gen/Show_card_briefly.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/card/Cards.hpp"
#include "RUtil/Text_Vector_Reader.hpp"

namespace Dungeon{
namespace GridScreenAction{
    void Grid_screen_upgrade_action::SetCard(const std::shared_ptr<Card::Cards> &card){
        this->is_done=false;
        this->is_cancelled=false;
        this->card=card;
        this->upgraded_card=card->Clone();
        this->upgraded_card->CallUpgrade(true);
        this->card->SetDrawScale(1.0F, true);
        this->upgraded_card->SetDrawScale(1.0F, true);
        confirm.show();
        cancel.show();
        // 設定取消按鈕的文字
        auto cancel_text = RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::GridCardSelectScreen)[1];
        cancel.set_text(cancel_text);
        
        // 設定確認按鈕的文字
        auto confirm_text = RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::GridCardSelectScreen)[0];
        confirm.set_text(confirm_text);
    }
    
    void Grid_screen_upgrade_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        arrow_update();
        confirm.update();
        cancel.update();
        if(cancel.is_logically_clicked()){
            is_cancelled=true;
        }else if(confirm.is_logically_clicked()){
            this->card->CallUpgrade();
            dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Card_upgrade_eff_gen>(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F));
            dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Show_card_briefly>(this->card));
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