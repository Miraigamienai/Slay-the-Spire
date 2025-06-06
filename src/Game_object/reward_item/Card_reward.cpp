#include "Game_object/reward_item/Card_reward.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Player.hpp"
#include "WindowSize.hpp"

namespace Reward{
    Card_reward::Card_reward(const std::vector<std::shared_ptr<Card::Cards>>&cards):chosen(false),hovered_card(nullptr),reward_cards(cards){
    }

    void Card_reward::Open(){
        skip_button.show();
        set_cards_pos();
    } 

    void Card_reward::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        this->skip_button.render(r2);
        for(const auto&it:this->reward_cards) it->render(r2);
    }

    void Card_reward::set_cards_pos()const{
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

    void Card_reward::update(Dungeon::Dungeon_shared &dungeon_shared){
        this->skip_button.update();
        //card update
        hovered_card=nullptr;
        for(const auto&it:reward_cards){
            it->update(dungeon_shared.top_effs);
            if(it->HitboxHovered()){
                this->hovered_card=it;
                it->Hover();
            }else{
                it->Unhover();
            }
        }
        if(hovered_card!=nullptr&&hovered_card->HitboxClicked()){
            //card chosen
            this->skip_button.hide();
            //obtain the card
            dungeon_shared.card_group_handler.obtain(hovered_card);
            //set chosen true
            this->chosen=true;
            //clear cards
            this->reward_cards.clear();
            
        }
    }
}