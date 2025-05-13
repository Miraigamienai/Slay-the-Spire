#pragma once

#include <memory>

//fwd decl
namespace Card{
    class Cards;
}

struct Shop_card_item
{
    std::shared_ptr<Card::Cards> card;
    int price;
};
