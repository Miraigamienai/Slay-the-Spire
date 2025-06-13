#pragma once

#include <algorithm>//shuffle
#include <SDL_stdinc.h>//uint32
#include <memory>

#include "Game_object/card/Cards.hpp"//inline function
#include "Game_object/Group_template.hpp"//father
#include "RUtil/Random.hpp"//rng

//fwd decl
namespace Draw{
    class Draw_2D;
}
namespace Effect{
    class Effect_group;
}

namespace Card{
class Card_group:public Template::Group_template<std::vector<std::shared_ptr<Cards>>>
{
public:
    Card_group()=default;
    ~Card_group()override=default;
    
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update(Effect::Effect_group &effs);
    void SortByRarity(const bool ascending);
    void MoveAllCardTo(Card_group &group);
    std::shared_ptr<Cards> GetHoveredCard()const;
    int GetCardPos(const std::shared_ptr<Cards> &card)const;
    void ShuffleWithRng(RUtil::Random &rng){
        std::shuffle(box.begin(),box.end(),rng);
    }
    bool CanUpgradeCard()const{
        for(const auto&it:box) if(!it->IsUpgraded()) return true;
        return false;
    }
    void AddCardAt(size_t idx, const std::shared_ptr<Cards>&card){
        box.insert(box.begin() + idx, card);
    }
    const std::shared_ptr<Cards>&operator[](size_t idx)const{return box[idx];}
    void CloneOther(const Card_group&other){
        box.clear();
        for(const auto&it:other) box.emplace_back(it->Clone());
    }
};
}