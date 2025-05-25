#include "Game_object/effect_gen/Exhaust_card_eff_gen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Exhaust_blur_eff.hpp"
#include "Game_object/effect/Exhaust_ember_eff.hpp"

namespace EffectGen
{
    void Exhaust_card_eff_gen::update(Dungeon::Dungeon_shared &dungeon_shared){
        //the card is already in the force_render when using card. 
        if(duration==DUR){
            for(int i=0;i<90;++i) dungeon_shared.effs.AddTop(std::make_shared<Effect::Exhaust_blur_eff>(card->GetX(), card->GetY()));
            for(int i=0;i<50;++i) dungeon_shared.effs.AddTop(std::make_shared<Effect::Exhaust_ember_eff>(card->GetX(), card->GetY()));
        }else if(duration<0.7F){
            this->card->SetColorAlpha(0.0F);
        }
        TimeGo();
        if(is_done){
            this->card->SetColorAlpha(1.0F,true);
        }
    }   
} // namespace EffectGen
