#include "Game_object/room/Rest_room.hpp"
#include "Game_object/room/rest_room_options/Option_handler.hpp"
#include "Game_object/effect/Camfire_burning_effect.hpp"
#include "Game_object/effect/Effect_pool.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Random.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Room
{
    void Rest_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(room_phase==Room_phase::complete){
            proceed.render(r2);
            return;
        }
        this->campfire_burning_effs.render(r2);
        if(this->option_handler!=nullptr)
            this->option_handler->render(r2);
        proceed.render(r2);
    }

    void Rest_room::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(room_phase==Room_phase::complete){
            proceed.update();
            return;
        }
        //TODO:player position
        //fire update
        campfire_burning_effs.update();
        campfire_burning_timer-=RUtil::Game_Input::delta_time();
        if(campfire_burning_timer<0.0F){
            campfire_burning_timer=BURNING_TIMER;
            add_fire();
            add_fire();
        }
        //option update
        if(option_handler!=nullptr){
            if(option_handler->someone_be_clicked()){
                option_handler->take_reward(dungeon_shared);
                if(option_handler->IsCancelled()){
                    option_handler->update();
                }else if(option_handler->IsDone()){
                    option_handler=nullptr;
                }
            }else{
                option_handler->update();
            }
        }
        //check the proceed button status
        if(dungeon_shared.manager.current_screen_equals(Interface::ScreenType::grid_cards)){
            //smith
            proceed_pop_timer=0.0F;
            proceed.hide();
        }else{
            //normal
            if(proceed_pop_timer>0.0F)
                proceed_pop_timer-=RUtil::Game_Input::delta_time();
            else
                proceed.show();
        }
        //update the proceed button
        proceed.update();
        if(proceed.is_logically_clicked()){
            //to main map
            dungeon_shared.manager.open<Interface::ScreenType::main_dungeon>();
            //hide button
            proceed.hide();
            //set phase
            room_phase=Room_phase::complete;
        }
    }
    
    void Rest_room::add_fire(){
        float color_g=1.0F - RUtil::Random::GetRandomFloat(0.0F, 0.5F);
        Uint32 burning_color=RUtil::Math::GetColorUint32_RGB(1.0F, color_g, 1.0F - color_g + RUtil::Random::GetRandomFloat(0.0F, 0.2F));
        this->campfire_burning_effs.AddTop(Effect::Effect_pool<Effect::Camfire_burning_effect>::GetEffect(burning_color));
    }

    void Rest_room::init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color){
        room_phase=Room_phase::just_complete;
        this->dungeon_fade_color=dungeon_fade_color;
        this->option_handler=std::make_shared<Option::Option_handler>(dungeon_shared, dungeon_fade_color);
    }

    const std::shared_ptr<Draw::ReTexture> &Rest_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/rest.png"),
                                           &Rest_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/restOutline.png");
} // namespace Room
