#pragma once

#include <memory>//shared_ptr
#include <utility>//std::forward

#include "Game_object/card/Cards.hpp"//base

namespace Interface{
//Inheriting from CardPrototype automatically inherits from Cards.
//Don't inherit from Cards again to avoid ambiguity.
template<typename Derived>
class CardPrototype : public Card::Cards{
public:
    template <typename...Args>
    CardPrototype(Args&&...args):Card::Cards(std::forward<Args>(args)...){}
    //CRPT
    std::shared_ptr<Card::Cards> Clone() const override {
        return std::make_shared<Derived>(static_cast<const Derived&>(*this));
    }
};
}