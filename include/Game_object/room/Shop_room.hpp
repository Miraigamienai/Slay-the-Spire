#pragma once

#include "Game_object/room/rooms.hpp"

//fwd decl
namespace Room{
    class Shop_merchant;
}

namespace Room{
class Shop_room final:public Rooms
{
public:
    Shop_room()noexcept:Rooms(Room_type::Shop),merchant(nullptr){}
    ~Shop_room()override=default;
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update(Dungeon::Dungeon_shared &dungeon_shared) override;
    void init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color) override;
private:
    std::shared_ptr<Shop_merchant> merchant;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static const std::shared_ptr<Draw::ReTexture> &IMG_O;
};
}
