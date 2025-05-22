#include "Game_object/room/Treasure_item.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReTexture.hpp"



namespace Room{
    Treasure_item::Treasure_item(
                                 const std::shared_ptr<Draw::ReTexture> &IMG_TREASURE,
                                 const std::shared_ptr<Draw::ReTexture> &IMG_OPENED_TREASURE)
        :hb(DRAW_X, DRAW_Y, HB_W, HB_H, false),
        IMG_TREASURE(IMG_TREASURE),IMG_OPENED_TREASURE(IMG_OPENED_TREASURE){}

    void Treasure_item::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{

        r2->SetColor(RUtil::WHITE);
        if(is_opened)
            r2->draw(IMG_OPENED_TREASURE, DRAW_X, DRAW_Y, OBJECT_W, OBJECT_H);
        else
            r2->draw(IMG_TREASURE, DRAW_X, DRAW_Y, OBJECT_W, OBJECT_H);
        
    }

    void Treasure_item::update(Dungeon::Dungeon_shared& dungeon_shared){
        if(dungeon_shared.manager.current_screen_equals(Interface::ScreenType::NONE)){
            this->hb.update();
            //open screen if the hb be clicked and the shop screen is not opening
            if(this->hb.Clicked()){
                dungeon_shared.manager.open<Interface::ScreenType::combat_reward>(get_reward(dungeon_shared));
                is_opened=true;
            }
        }
    }
   
}