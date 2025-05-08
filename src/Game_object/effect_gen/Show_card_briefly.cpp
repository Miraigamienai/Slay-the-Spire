#include "Game_object/effect_gen/Show_card_briefly.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/Card_pos_setter.hpp"

namespace EffectGen
{
    Show_card_briefly::Show_card_briefly(const std::shared_ptr<Card::Cards>&card)
        :card(card)
    {
        Card::set_card_pos(this->card, s_cnt);
        ++s_cnt;
        this->duration=2.5F;
        this->card->SetDrawScale(0.01F, true);
        this->card->SetDrawScale(1.0F);
    }

    void Show_card_briefly::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(this->duration==2.5F){//first in
            //force render
            dungeon_shared.card_group_handler.AddBot<Card::GroupType::force_render_cards>(card);
        }else if(this->duration<0.6F){
            this->card->SetColorAlpha(0.0F);
        }
        this->card->update(dungeon_shared.top_effs);
        TimeGo();
        if(this->is_done){
            --s_cnt;
            this->card->SetColorAlpha(1.0F,true);
            dungeon_shared.card_group_handler.erase<Card::GroupType::force_render_cards>(card);//remove from force render
        }
    }

    int Show_card_briefly::s_cnt;
} // namespace Effect
