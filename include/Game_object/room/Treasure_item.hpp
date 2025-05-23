#pragma once

#include <memory>
#include <array>

#include "Game_object/room/Shop_item.hpp"
#include "RUtil/Hitbox.hpp"
#include "WindowSize.hpp"
#include <vector>
#include "Game_object/reward_item/Reward_item.hpp"

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
class Treasure_item
{
public:
    Treasure_item(const std::shared_ptr<Draw::ReTexture> &IMG_TREASURE,const std::shared_ptr<Draw::ReTexture> &IMG_OPENED_TREASURE);
    ~Treasure_item()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update(Dungeon::Dungeon_shared& dungeon_shared);
    virtual std::vector<std::shared_ptr<Reward::Reward_item>> get_reward(Dungeon::Dungeon_shared& dungeon_shared)const=0;
private:
    RUtil::Hitbox hb;
    bool is_opened=false;

    const std::shared_ptr<Draw::ReTexture> &IMG_TREASURE,&IMG_OPENED_TREASURE;

    static constexpr float HB_W = 300.0F * Setting::SCALE,
                           HB_H = 250.0F * Setting::SCALE;
    static constexpr float DRAW_X = Setting::WINDOW_WIDTH*0.6F,
                           DRAW_Y = Setting::WINDOW_HEIGHT*0.5F-300.0F*Setting::SCALE,
                           OBJECT_W= 300.0F * Setting::SCALE,
                           OBJECT_H= 250.0F * Setting::SCALE;
        
};

}