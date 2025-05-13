#include "Game_object/dungeon/Dungeon_manager.hpp"
#include "Util/Logger.hpp"

namespace Dungeon{
    Dungeon_manager::Dungeon_manager(){
        m_dungeon_screen=std::make_shared<Dungeon::Dungeon_screen>();
        combat_reward_screen=std::make_shared<Dungeon::Combat_reward_screen>();
        grid_card_screen=std::make_shared<Dungeon::Grid_card_screen>();
        shop_screen=std::make_shared<Dungeon::Shop_screen>();
        current_screen=m_dungeon_screen;
    }
    void Dungeon_manager::update(Dungeon_shared &dungeon_shared){
        if(last_screen!=nullptr) last_screen->update(dungeon_shared);
        if(current_screen!=nullptr){
            current_screen->update(dungeon_shared);
            //because maybe current_screen will be nullptr after update.
            if(current_screen!=nullptr&&!current_screen->is_on_top()) switch_to_next_screen();
        }
    }
    void Dungeon_manager::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(last_screen!=nullptr) last_screen->render(r2);
        if(current_screen!=nullptr)current_screen->render(r2);
    }
    void Dungeon_manager::switch_to_next_screen(){
        last_screen=current_screen;
        current_screen=GetScreen(last_screen->get_next());
        if(current_screen!=nullptr){
            current_screen->set_on_opening();
        }
    }
}