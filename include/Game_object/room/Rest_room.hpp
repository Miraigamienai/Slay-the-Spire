#pragma once

#include "Game_object/room/rooms.hpp"
#include "Game_object/effect/Effect_group.hpp"
#include "RUtil/ColorValuesOnly.hpp"

namespace Room{
//fwd decl
namespace Option{
class Option_handler;
}

class Rest_room final:public Rooms
{
public:
    Rest_room():Rooms(Room_type::Rest),option_handler(nullptr),dungeon_fade_color(RUtil::BLACK),campfire_burning_timer(BURNING_TIMER){}
    ~Rest_room()override=default;
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update(Dungeon::Dungeon_shared &dungeon_shared) override;
    void init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color) override;
private:
    std::shared_ptr<Option::Option_handler> option_handler;
    Uint32 dungeon_fade_color;
    Effect::Effect_group campfire_burning_effs;
    float campfire_burning_timer;

    void add_fire();
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static const std::shared_ptr<Draw::ReTexture> &IMG_O;
    static constexpr float BURNING_TIMER=0.05F;
};
}