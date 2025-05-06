#include "Game_object/room/rest_room_options/Option_handler.hpp"
#include "Game_object/room/rest_room_options/Rest_option.hpp"
#include "Game_object/room/rest_room_options/Smith_option.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Player.hpp"
#include "Draw/Draw_2D.hpp"

namespace Room{
namespace Option{
    Option_handler::Option_handler(const Dungeon::Dungeon_shared& dungeon_shared){
        //rest option
        opts.emplace_back(std::make_shared<Rest_option>(dungeon_shared.player->GetMaxHP()));
        //smite option
        opts.emplace_back(std::make_shared<Smith_option>(dungeon_shared.card_group_handler.can_upgrade_card()));
        set_opts_pos();
    }

    void Option_handler::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        //TODO:font
        //options
        for(const auto&it:opts) it->render(r2);

    }
    
    void Option_handler::update(){
        for(const auto&it:opts){
            it->update();
        }
    }

    void Option_handler::set_opts_pos(){
        for(size_t i=0;i<opts.size();i++){
            //x
            int now_x=BUTTON_START_X;//left
            if(i==opts.size()-1 && (opts.size()&1)==1){
                //last and middle
                now_x+=BUTTON_SPACING_X/2.0F;
            }else if((i&1)==0){
                //right
                now_x+=BUTTON_SPACING_X;
            }

            //y
            int now_y=BUTTON_START_Y;
            if(i>=2){
                now_y+=(i>>1)*BUTTON_SPACING_Y + BUTTON_EXTRA_SPACING_Y;
            }

            opts[i]->move(now_x,now_y);
        }   
    }
}
}