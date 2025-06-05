#include "Game_object/room/Elite_room.hpp"
#include "RUtil/Image_book.hpp"

namespace Room{
const std::shared_ptr<Draw::ReTexture> &Elite_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/elite.png"),
                                       &Elite_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/elite.png");
}