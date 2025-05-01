#include "Game_object/effect_gen/Show_card_to_discard.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Player.hpp"//just for get color?
#include "Game_object/effect_gen/Card_paticle_gen.hpp"
#include "RUtil/Random.hpp"
#include "WindowSize.hpp"

namespace EffectGen{
    Show_card_to_discard::Show_card_to_discard(std::shared_ptr<Card::Cards> card):card(card){
        this->duration=ACTION_DUR_XLONG;
        set_card_pos();
        this->card->SetDrawScale(0.01F,true);
        this->card->SetDrawScale(1.0F);

    }

    void Show_card_to_discard::set_card_pos()const{
        constexpr float PADDING=30.0F*Setting::SCALE;
        this->card->SetY(static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F);
        switch(s_cnt){
            case 0:
                this->card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F);
                break;
            case 1:
                this->card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F - PADDING - Card::Cards::IMG_WIDTH);
                break;
            case 2:
                this->card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F + PADDING + Card::Cards::IMG_WIDTH);
                break;
            case 3:
                this->card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F - (PADDING + Card::Cards::IMG_WIDTH)*2.0F);
                break;
            case 4:
                this->card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F + (PADDING + Card::Cards::IMG_WIDTH)*2.0F);
                break;
            default:
                this->card->SetX(RUtil::Random::GetRandomFloat(0.1F,0.9F)*Setting::SCALE);
                this->card->SetY(RUtil::Random::GetRandomFloat(0.2F,0.8F)*Setting::SCALE);
                break;
        }
        s_cnt++;
    }

    void Show_card_to_discard::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(this->duration==ACTION_DUR_XLONG){//first in
            dungeon_shared.gen_group.AddTop(std::make_shared<Card_paticle_gen>(card->GetTargetX(), card->GetTargetY()));
            //add to discard at first update
            dungeon_shared.card_group_handler.AddBot<Card::GroupType::m_discard>(this->card);
            //force render
            dungeon_shared.card_group_handler.AddBot<Card::GroupType::force_render_cards>(card);
        }
        TimeGo();
        this->card->update(dungeon_shared.top_effs, dungeon_shared.player->GetCardTrailColor());
        if(this->is_done){
            s_cnt--;
            dungeon_shared.card_group_handler.discard(card,true);//visual only
            dungeon_shared.card_group_handler.erase<Card::GroupType::force_render_cards>(card);//remove from force render
        }
    }

    int Show_card_to_discard::s_cnt=0;
}