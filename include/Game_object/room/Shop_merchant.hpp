#pragma once

#include <memory>
#include <array>

#include "Game_object/room/Shop_item.hpp"
#include "RUtil/Hitbox.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
    class ReTexture;
}
namespace Dungeon{
    struct Dungeon_shared;        
}
namespace Card{
    class Cards;
}

namespace Room{
class Shop_merchant
{
public:
    Shop_merchant(Dungeon::Dungeon_shared& dungeon_shared);
    ~Shop_merchant()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update(Dungeon::Dungeon_shared& dungeon_shared);
private:
    RUtil::Hitbox hb;
    std::array<Shop_card_item, 5> card1;   
    std::array<Shop_card_item, 2> card2;
    
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr float HB_W = 360.0F * Setting::SCALE,
                           HB_H = 300.0F * Setting::SCALE;
    static constexpr float DRAW_X = static_cast<float>(Setting::WINDOW_WIDTH)/2.0F + 34.0F * Setting::SCALE,
                           DRAW_Y = (340.0F - 109.0F) * Setting::SCALE;
};
}