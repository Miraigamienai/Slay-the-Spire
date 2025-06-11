#include "Game_object/effect_gen/Purge_card_eff_gen.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Damage_impact_curvy_eff.hpp"
#include "Game_object/effect/Purge_card_eff.hpp"
#include "Game_object/Card_pos_setter.hpp"
#include "RUtil/Some_Math.hpp"

namespace EffectGen{
    static inline constexpr auto GetColor1(Card::Color card_color){
        switch(card_color){
            case Card::Color::red:return RUtil::Math::GetColorUint32_RGB(0.1F, 0.4F, 0.7F);
            case Card::Color::green:return RUtil::Math::GetColorUint32_RGB(0.4F, 0.4F, 0.4F);
            case Card::Color::blue:return RUtil::Math::GetColorUint32_RGB(0.2F, 0.7F, 0.2F);
            case Card::Color::purple:return RUtil::Math::GetColorUint32_RGB(0.9F, 0.3F, 0.2F);
            default:return RUtil::Math::GetColorUint32_RGB(0.2F, 0.15F, 0.2F);
        }
    }

    static inline constexpr auto GetColor2(Card::Rarity card_rarity){
        switch(card_rarity){
            case Card::Rarity::basic:return RUtil::Math::GetColorUint32_RGB(0.2F, 0.8F, 0.8F);
            case Card::Rarity::curse:return RUtil::Math::GetColorUint32_RGB(0.8F, 0.7F, 0.2F);
            default:return RUtil::Math::GetColorUint32_RGB(0.6F, 0.6F, 0.6F);
        }
    }

    Purge_card_eff_gen::Purge_card_eff_gen(const std::shared_ptr<Card::Cards> &card)
        :card(card),
        first(false)
    {
        Card::set_card_pos(this->card, s_cnt);
        ++s_cnt;
        this->duration=2.0F;
        this->card->SetDrawScale(0.01F, true);
        this->card->SetDrawScale(1.0F);
    }
    
    void Purge_card_eff_gen::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(this->duration==2.0F){
            dungeon_shared.top_effs.AddTop(std::make_shared<Effect::Purge_card_eff>(card, GetColor1(card->color), GetColor2(card->rarity)));
        }if(!first&&this->duration<0.5F){
            first=true;
            this->card->SetColorAlpha(0.0F);
            for(int i=0;i<16;i++) dungeon_shared.top_effs.AddTop(std::make_shared<Effect::Damage_impact_curvy_eff>(glm::vec2{card->GetX(), card->GetY()},GetColor1(card->color)));
            for(int i=0;i<8;i++) dungeon_shared.effs.AddTop(std::make_shared<Effect::Damage_impact_curvy_eff>(glm::vec2{card->GetX(), card->GetY()},GetColor2(card->rarity)));
        }
        this->card->update(dungeon_shared.top_effs);
        TimeGo();
        if(this->is_done){
            this->card->SetColorAlpha(1.0F,true);
        }
    }

    int Purge_card_eff_gen::s_cnt=0;
}