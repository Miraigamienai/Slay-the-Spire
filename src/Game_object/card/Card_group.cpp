#include "Game_object/card/Card_group.hpp"//the hpp
#include "Game_object/card/Cards.hpp"//cards
#include "Game_object/effect/Effect_group.hpp"//effs
#include "Draw/Draw_2D.hpp"//for rendering

#include "Util/Logger.hpp"

namespace Card{
    void Card_group::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        for(const auto &it:box){
            it->render(r2);
        }
    }
    void Card_group::update(Effect::Effect_group &top_effs){
        for(auto &it:box){
            it->update(top_effs);
        }
    }
    void Card_group::MoveAllCardTo(Card_group &group){
        group.box.insert(group.box.end(), std::make_move_iterator(this->box.rbegin()), std::make_move_iterator(this->box.rend()));
        this->box.clear();
    }
    
    static constexpr auto RarityWeight=[]()constexpr{
        std::array<int, 6> temp{};
        temp[static_cast<int>(Rarity::basic)]   = 0;
        temp[static_cast<int>(Rarity::common)]  = 1;
        temp[static_cast<int>(Rarity::uncommon)]= 2;
        temp[static_cast<int>(Rarity::rare)]    = 3;
        temp[static_cast<int>(Rarity::special)] = 4;
        temp[static_cast<int>(Rarity::curse)]   = 5;
        return temp;
    }();
    void Card_group::SortByRarity(const bool ascending){
        //sort by text id to make sure the same card will together
        std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return static_cast<int>(aa->card_text_id) < static_cast<int>(bb->card_text_id);});
        //sort by rarity
        if(ascending)std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return RarityWeight[static_cast<int>(aa->rarity)] < RarityWeight[static_cast<int>(bb->rarity)];});
        else std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return RarityWeight[static_cast<int>(aa->rarity)] > RarityWeight[static_cast<int>(bb->rarity)];});
    }

    std::shared_ptr<Cards> Card_group::GetHoveredCard()const{
        for(const auto&it:box){
            if(it->IsHoveredInHand(0.7F)){
                return it;
            }
        }
        return nullptr;
    }
    int Card_group::GetCardPos(const std::shared_ptr<Cards> &card)const{
        const int len=static_cast<int>(box.size());
        for(int i=0;i<len;i++) if(box[i]==card) return i;
        return -1;
    }
}