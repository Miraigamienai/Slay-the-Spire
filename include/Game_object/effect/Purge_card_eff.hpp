#pragma once

#include "Game_object/effect/Effects.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Card{
    class Cards;
}

namespace Effect{
class Purge_card_eff final:public Effects
{
public:
    Purge_card_eff(const std::shared_ptr<Card::Cards> &card, Uint32 color1, Uint32 color2)
        :card(card),
        color2(color2),
        scale2(Setting::SCALE)
    {
        this->color=color;
        this->color_a=0.01F;
        this->duration=2.0F;
        this->scale=Setting::SCALE;
    }
    ~Purge_card_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    std::shared_ptr<Card::Cards> card;
    Uint32 color2;
    float scale2;
};
}