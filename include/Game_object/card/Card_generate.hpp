#pragma once

#include <memory>

//fwd decl
namespace Card{
    class Cards;
}
namespace RUtil{
    class Random;
}

namespace Card{
class Card_generate
{
public:
    Card_generate()=delete;~Card_generate()=delete;Card_generate(const Card_generate &) = delete;Card_generate(Card_generate &&) = delete;Card_generate &operator=(const Card_generate &) = delete;Card_generate &operator=(Card_generate &&) = delete;
    static std::shared_ptr<Card::Cards> GetRandomRedCard(RUtil::Random &rng);
private:

};
}