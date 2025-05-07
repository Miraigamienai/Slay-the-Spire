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
    
    void Card_group::SortByRarity(const bool ascending){
        if(ascending)std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return aa->rarity<bb->rarity;});
        else std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return bb->rarity<aa->rarity;});
    }
    void Card_group::SortByType(const bool ascending){
        if(ascending)std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return aa->type<bb->type;});
        else std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return bb->type<aa->type;});
    }
    void Card_group::SortByCost(const bool ascending){
        if(ascending)std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return aa->GetCost()<bb->GetCost();});
        else std::sort(box.begin(),box.end(),[](const auto&aa,const auto&bb){return bb->GetCost()<aa->GetCost();});
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
    Card_group& Card_group::operator=(const Card_group&other){
        box.clear();
        for(const auto&it:other) box.emplace_back(it->Clone());
        return *this;
    }
}