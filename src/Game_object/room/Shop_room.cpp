#include "Game_object/room/Shop_room.hpp"
#include "Game_object/room/Shop_merchant.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Room
{
    void Shop_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        merchant->render(r2);
        proceed.render(r2);
    }

    void Shop_room::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(room_phase==Room_phase::complete){
            proceed.update();
            return;
        }
        merchant->update(dungeon_shared);
        //check the proceed button status
        if(!dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::NONE)){
            //already open the shop screen
            proceed_pop_timer=0.0F;
            proceed.hide();
        }else{
            //not open
            if(proceed_pop_timer>0.0F)
                proceed_pop_timer-=RUtil::Game_Input::delta_time();
            else
                proceed.show();
        }
        //update the proceed button
        proceed.update();
        if(proceed.is_logically_clicked()){
            //to main map
            dungeon_shared.manager.open<Abstraction::ScreenType::main_dungeon>();
            //hide button
            proceed.hide();
            //set phase
            room_phase=Room_phase::complete;
        }
    }

    void Shop_room::init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 /* dungeon_fade_color */){
        room_phase=Room_phase::just_complete;
        merchant=std::make_shared<Shop_merchant>(dungeon_shared);   
    }

    const std::shared_ptr<Draw::ReTexture> &Shop_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/shop.png"),
                                           &Shop_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/shopOutline.png");
} // namespace Room
