#include "Game_object/effect_gen/Show_card_to_hand.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect_gen/Card_paticle_gen.hpp"
#include "Game_object/Card_pos_setter.hpp"
#include "RUtil/Random.hpp"
#include "WindowSize.hpp"
#include <iostream>
namespace EffectGen{
    Show_card_to_hand::Show_card_to_hand(const std::shared_ptr<Card::Cards> &card):card(card){
        this->duration=ACTION_DUR_XLONG;
        Card::set_card_pos(card, s_cnt);
        ++s_cnt;
        this->card->SetDrawScale(0.01F,true);
        this->card->SetDrawScale(1.0F);
    }

    void Show_card_to_hand::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(this->duration==ACTION_DUR_XLONG){//first in
            dungeon_shared.gen_group.AddTop(std::make_shared<Card_paticle_gen>(card->GetTargetX(), card->GetTargetY()));
            //add to draw_pile at first update
            dungeon_shared.card_group_handler.AddBot<Card::GroupType::hand_cards>(this->card);
            //force render
            // dungeon_shared.card_group_handler.AddBot<Card::GroupType::force_render_cards>(card);
        }
        TimeGo();
        this->card->update(dungeon_shared.top_effs);
        if(this->is_done){
            --s_cnt;
            // dungeon_shared.card_group_handler.discard(card,true);
            // dungeon_shared.card_group_handler.shuffle(false);//visual only
            // dungeon_shared.card_group_handler.erase<Card::GroupType::force_render_cards>(card);//remove from force render
        }
    }

    int Show_card_to_hand::s_cnt=0;
}