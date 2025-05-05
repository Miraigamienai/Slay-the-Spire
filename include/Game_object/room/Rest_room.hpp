#pragma once

#include "Game_object/room/rooms.hpp"
#include "Game_object/effect/Effect_group.hpp"

namespace Room{
class Rest_room final:public Rooms
{
public:
    Rest_room();
    ~Rest_room()override=default;
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update(Dungeon::Dungeon_shared &dungeon_shared) override;
    void init_room(RUtil::Random_package &random_package) override;
private:

    // Effect::Effect_group campfire_bubbles;//
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static const std::shared_ptr<Draw::ReTexture> &IMG_O;
};
}