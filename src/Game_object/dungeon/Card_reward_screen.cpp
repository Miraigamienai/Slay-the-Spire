#include "Game_object/dungeon/Card_reward_screen.hpp"
#include "Game_object/card/Cards.hpp"
#include "WindowSize.hpp"

namespace Dungeon{
    Card_reward_screen::Card_reward_screen(){
        hovered_card=nullptr;
    }

    void Card_reward_screen::Open(const std::vector<std::shared_ptr<Card::Cards>>&cards){
        this->reward_cards=cards;
        set_cards_pos();
    } 

    void Card_reward_screen::set_cards_pos()const{
        constexpr float Y=static_cast<float>(Setting::WINDOW_HEIGHT)*0.45F;
        constexpr float X=static_cast<float>(Setting::WINDOW_WIDTH)/2.0F;
        constexpr float PAD=40.0F*Setting::SCALE;
        for(size_t i=0;i<reward_cards.size();++i){
            reward_cards[i]->SetDrawScale(0.75F,true);
            reward_cards[i]->SetY(Y,true);
            reward_cards[i]->SetX(X,true);
            reward_cards[i]->SetX(X + (static_cast<float>(i) - (static_cast<float>(reward_cards.size()) - 1.0F)/2.0F) * (Card::Cards::IMG_WIDTH + PAD));
        }
    }
}