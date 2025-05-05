#include "Game_object/room/Rest_room.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

namespace Room
{
    void Rest_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{

    }
    void Rest_room::update(Dungeon::Dungeon_shared &dungeon_shared){
        //TODO:player position
        //eff update
        //eff
        //hidden
    }
    void Rest_room::init_room(RUtil::Random_package &random_package){

    }

    const std::shared_ptr<Draw::ReTexture> &Rest_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monster.png"),
                                           &Rest_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monsterOutline.png");
} // namespace Room
