#include "RUtil/Game_Input.hpp"
#include "Game_object/dungeon/Dungeon_screen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/map/Map_node.hpp"

#include "Util/Logger.hpp"

namespace Dungeon
{
    Dungeon_screen::Dungeon_screen()
        :Abstraction::Is_screen(Abstraction::ScreenType::main_dungeon),
        the_map(offset_y,on_top),
        offset_y(-100.0F * Setting::SCALE),
        target_offset_y(offset_y),
        scroll_wait_timer(0.0F),
        scroll(offset_y, target_offset_y, MAP_SCROLL_LOWER, MAP_UPPER_SCROLL_NORMAL)
    {
        on_top=true;
    }

    void Dungeon_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(the_map.get_alpha()!=0.0F){
            the_map.render(r2);
            if(display_map!=nullptr){
                for(const auto&it:*display_map)
                    for(const auto&it2:it)
                        if(it2!=nullptr)it2->render(r2,offset_y,the_map.get_alpha());
            }else{
                LOG_ERROR("Forget to set the dispaly_map.");
            }
            the_map.render_boss_icon(r2);
        }
    }

    void Dungeon_screen::open(){
        this->the_map.show();
        //TODO: offset y setting
    }

    void Dungeon_screen::update(Dungeon_shared &dungeon_shared){
        the_map.update();
        bool pause_offset_y_update=false;
        if(display_map!=nullptr){
            for(const auto&it:*display_map)
                for(const auto&it2:it)
                    if(it2!=nullptr){
                        it2->update(offset_y,true,on_top,dungeon_shared.top_effs);
                        if(it2->IsMakingCircle()){
                            pause_offset_y_update=true;
                        }
                    }
        }else{
            LOG_ERROR("Forget to set the dispaly_map.");
        }

        if(on_top&&!pause_offset_y_update){
            if(scroll_wait_timer<=0.0F){
                this->scroll.update();
            }else if(scroll_wait_timer<3.0F){
                offset_y = RUtil::Math::interpolation_exp10(MAP_SCROLL_LOWER, MAP_UPPER_SCROLL_NORMAL, scroll_wait_timer / 3.0F);
            }else{
                scroll_wait_timer-=RUtil::Game_Input::delta_time();
            }
        }
    }
    
    void Dungeon_screen::set_display_map(const std::vector<std::vector<std::shared_ptr<Map::Map_node>>>&map, const std::shared_ptr<Draw::ReTexture> &boss_icon, const std::shared_ptr<Draw::ReTexture> &boss_outline){
        for(const auto&it:map)
            for(const auto&it2:it)
                if(it2!=nullptr)it2->BindLegend(this->the_map.GetLegend());
        display_map=&map;
        the_map.set_boss(boss_icon, boss_outline);
    }
} // namespace Dungeon
