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

namespace Room
{
    void Rest_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        this->campfire_burning_effs.render(r2);
        this->option_handler->render(r2);
    }

    void Rest_room::update(Dungeon::Dungeon_shared &dungeon_shared){
        //TODO:player position
        //fire update
        campfire_burning_timer-=RUtil::Game_Input::delta_time();
        if(campfire_burning_timer<0.0F){
            campfire_burning_timer=BURNING_TIMER;
            add_fire();
            add_fire();   
        }
        //chheck
        //eff update
        //eff
        //hidden
    }
    
    void Rest_room::add_fire(){
        float color_g=1.0F - RUtil::Random::GetRandomFloat(0.0F, 0.5F);
        Uint32 burning_color=RUtil::Math::GetColorUint32_RGB(1.0F, color_g, 1.0F - color_g + RUtil::Random::GetRandomFloat(0.0F, 0.2F));
        this->campfire_burning_effs.AddTop(Effect::Effect_pool<Effect::Camfire_burning_effect>::GetEffect(burning_color));
    }

    void Rest_room::init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color){
        this->dungeon_fade_color=dungeon_fade_color;
        this->option_handler=std::make_shared<Option::Option_handler>(dungeon_shared, dungeon_fade_color);
    }

    const std::shared_ptr<Draw::ReTexture> &Rest_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monster.png"),
                                           &Rest_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monsterOutline.png");
} // namespace Room
