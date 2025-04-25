#pragma once

#include <algorithm>//shuffle
#include <SDL_stdinc.h>//uint32
#include <memory>

#include "Game_object/Group_template.hpp"//father
#include "RUtil/Random.hpp"//rng

//fwd decl
namespace Card{
    class Cards;
}
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
    Card_group(const Card_group&) = delete;
    Card_group(Card_group&&) = delete;
    Card_group& operator=(Card_group&&) = delete;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 PlayerColor_RGB)const;
    void update(Effect::Effect_group &effs,const Uint32 PlayerColor_RGB);
    void SortByRarity(const bool ascending);
    void SortByType(const bool ascending);
    void SortByCost(const bool ascending);
    void MoveAllCardTo(Card_group &group);
    void RemoveCard(const std::shared_ptr<Cards>&card);
    std::shared_ptr<Cards> GetHoveredCard()const;
    int GetCardPos(const std::shared_ptr<Cards> &card)const;
    void ShuffleWithRng(RUtil::Random &rng){
        std::shuffle(box.begin(),box.end(),rng);
    }

    const std::shared_ptr<Cards>&operator[](size_t idx)const{return box[idx];}
    Card_group& operator=(const Card_group&other);
};
}