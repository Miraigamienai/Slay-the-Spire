#include "Game_object/room/Shop_room.hpp"
#include "Draw/ReTexture.hpp"
#include "RUtil/Image_book.hpp"

namespace Room
{
    void Shop_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{

    }

    void Shop_room::update(Dungeon::Dungeon_shared &dungeon_shared){

    }

    void Shop_room::init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color){

    }

    const std::shared_ptr<Draw::ReTexture> &Shop_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/shop.png"),
                                           &Shop_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/shopOutline.png");
} // namespace Room
