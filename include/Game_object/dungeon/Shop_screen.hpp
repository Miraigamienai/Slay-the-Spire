#pragma once

#include <array>
#include <memory>

#include "Game_object/interface/Is_screen.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Card{
    class Cards;
}
namespace Effect{
    class Effect_group;
}

namespace Dungeon{
class Shop_screen final:public Interface::Is_screen
{
public:
    Shop_screen();
    ~Shop_screen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void open(std::array<std::shared_ptr<Card::Cards>, 5> card1, std::array<std::shared_ptr<Card::Cards>, 2> card2){
        this->card1=card1;
        this->card2=card2;
        this->current_y=static_cast<float>(Setting::WINDOW_HEIGHT);
        this->hand_x = this->hand_target_x = static_cast<float>(Setting::WINDOW_WIDTH)/2.0F;
        this->hand_y = this->hand_target_y = static_cast<float>(Setting::WINDOW_HEIGHT);
        this->hand_timer=1.0F;
    }    
private:
    std::array<std::shared_ptr<Card::Cards>, 5> card1;   
    std::array<std::shared_ptr<Card::Cards>, 2> card2;
    float current_y;
    float hand_timer;
    float hand_x, hand_target_x;
    float hand_y, hand_target_y;
    void hand_update();
    void cards_update(Effect::Effect_group &top_effs)const;
    static constexpr float TOP_ROW_Y = 760.0F * Setting::SCALE,
                           BOTTOM_ROW_Y = 337.0F * Setting::SCALE;
};
}