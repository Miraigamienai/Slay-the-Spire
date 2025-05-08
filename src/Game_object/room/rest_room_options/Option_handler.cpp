#include <glm/gtc/constants.hpp>//two pi

#include "Game_object/room/rest_room_options/Option_handler.hpp"
#include "Game_object/room/rest_room_options/Rest_option.hpp"
#include "Game_object/room/rest_room_options/Smith_option.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Player.hpp"
#include "Game_object/effect/Camfire_bubble_effect.hpp"
#include "Draw/Draw_2D.hpp"

namespace Room{
namespace Option{
    Option_handler::Option_handler(const Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color)
        :now_clicked_opt(nullptr),
        bubble_oscillate_timer(RUtil::Random::GetRandomFloat(0.0F, glm::two_pi<float>()))
    {
        //rest option
        opts.emplace_back(std::make_shared<Rest_option>(dungeon_shared.player->GetMaxHP(), dungeon_fade_color));
        //smite option
        opts.emplace_back(std::make_shared<Smith_option>(dungeon_shared.card_group_handler.can_upgrade_card()));
        set_opts_pos();

        more_bubble=opts.size()>2;
    }

    void Option_handler::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        bubbles.render(r2);
        //options
        for(const auto&it:opts) it->render(r2);
        //TODO:font
    }
    
    void Option_handler::update(){
        //opts update
        now_clicked_opt=nullptr;
        for(const auto&it:opts){
            it->update();
            if(it->is_logically_clicked()){
                now_clicked_opt=it;
            }
        }
        //bubbles update
        bubbles.update();
        bubble_oscillate_timer += 2.0F*RUtil::Game_Input::delta_time();
        bubble_offset = std::sin(bubble_oscillate_timer)*1.25F;
        if(bubbles.size()<(more_bubble? MORE_BUBBLE_AMOUNT : NORMAL_BUBBLE_AMOUNT)){
            const int temp = (more_bubble? MORE_BUBBLE_AMOUNT : NORMAL_BUBBLE_AMOUNT) - bubbles.size();
            for(int i=0;i<temp;++i){
                bubbles.AddTop(std::make_shared<Effect::Camfire_bubble_effect>(950.0F*Setting::SCALE, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F + 60.0F*Setting::SCALE, more_bubble, bubble_offset));
            }
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