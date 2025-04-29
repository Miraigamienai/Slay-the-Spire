#pragma once

#include <memory>

//fwd decl
namespace Monster{
    class Monsters;
}
namespace Card{
    class Cards;
}

namespace Card{
struct Card_item
{ 
    std::shared_ptr<Cards> card;
    std::shared_ptr<Monster::Monsters> monster;
};
}