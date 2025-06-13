#include "Game_object/room/Treasure_room.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/room/Treasure_item.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Game_object/room/Treasure_type/Large_chest.hpp"
#include "Game_object/room/Treasure_type/Medium_chest.hpp"
#include "Game_object/room/Treasure_type/Small_chest.hpp"
#include "RUtil/Random.hpp"
namespace Room
{
    void Treasure_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        treasure_item->render(r2);
        proceed.render(r2);
    }

    void Treasure_room::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(room_phase==Room_phase::complete){
            proceed.update();
            return;
        }
        treasure_item->update(dungeon_shared);
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
        treasure_item->update(dungeon_shared);
    }

    void Treasure_room::init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 /* dungeon_fade_color */){
        room_phase=Room_phase::just_complete;
        switch (static_cast<Treasure::Treasure_type> (dist(dungeon_shared.random_package.misc_rng)))
        {
        case Treasure::Treasure_type::SMALL:
            treasure_item=std::make_shared<Small_chest>();
            break;
        case Treasure::Treasure_type::MEDIUM:
            treasure_item=std::make_shared<Medium_chest>();
            break;
        case Treasure::Treasure_type::LARGE:
            treasure_item=std::make_shared<Large_chest>();
            break;
        default:
            break;
        }
        // 設定前進按鈕的文字
        auto proceed_text = RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::AbstractDungeon)[0];
        proceed.set_text(proceed_text);
    }
    std::discrete_distribution<int> Treasure_room::dist{Probability,Probability+3};
    const std::shared_ptr<Draw::ReTexture> &Treasure_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/chest.png"),
                                            &Treasure_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/chestOutline.png");

} // namespace Room
