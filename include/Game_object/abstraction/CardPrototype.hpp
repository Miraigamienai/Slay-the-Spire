#pragma once

#include <memory>//shared_ptr
#include <utility>//std::forward

#include "Game_object/card/Cards.hpp"//base

namespace Abstraction{
//Inheriting from CardPrototype automatically inherits from Cards.
//Don't inherit from Cards again to avoid ambiguity.
template<typename Derived>
class CardPrototype : public Card::Cards{
public:
    template <typename...Args>
    CardPrototype(Args&&...args):Card::Cards(std::forward<Args>(args)...){}
    std::shared_ptr<Card::Cards> Clone() const override {
        auto temp = std::make_shared<Derived>();
        if(this->upgraded) temp->CallUpgrade();
        return temp;
    }
};
}