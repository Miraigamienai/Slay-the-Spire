#ifndef GAME_OBJECT_DUNGEON_DUNGEON_MANAGER
#define GAME_OBJECT_DUNGEON_DUNGEON_MANAGER

#include <utility>

#include "Game_object/dungeon/Dungeon_screen.hpp"
#include "Game_object/dungeon/Combat_reward_screen.hpp"
#include "Game_object/map/Map_node.hpp"

namespace Dungeon{
    //This class will auto change where need to update or render.
    class Dungeon_manager
    {
    public:
        Dungeon_manager();
        ~Dungeon_manager()=default;
        void update(Dungeon_shared &dungeon_shared);
        void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
        void set_display_map(const std::vector<std::vector<std::shared_ptr<Map::Map_node>>>&map)const{m_dungeon_screen->set_display_map(map);}
        void set_current_on_top(bool value)const{current_screen->set_on_top(value);}
        void hide_dungeon_screen_instantly()const{m_dungeon_screen->hide_instantly();}
        template <Interface::ScreenType ST, typename ...Args>
        void open(Args&&...args){
            last_screen=current_screen;
            current_screen=GetScreen<ST>();
            if(last_screen==current_screen) last_screen=nullptr;
            current_screen->set_on_top(true);
            GetScreen<ST>()->open(std::forward<Args>(args)...);
        }
    private:
        std::shared_ptr<Interface::Is_screen> current_screen=nullptr,last_screen=nullptr;
        std::shared_ptr<Dungeon::Dungeon_screen> m_dungeon_screen;
        std::shared_ptr<Dungeon::Combat_reward_screen> combat_reward_screen;
        
        void switch_to_next_screen();
        template <Interface::ScreenType ST>
        const auto &GetScreen()const{
            if constexpr(ST==Interface::ScreenType::main_dungeon)
                return m_dungeon_screen;
            else if constexpr(ST==Interface::ScreenType::combat_reward)
                return combat_reward_screen;
        }
        std::shared_ptr<Interface::Is_screen> GetScreen(Interface::ScreenType ST)const{
            using namespace Interface;
            switch(ST){
                case ScreenType::main_dungeon: return m_dungeon_screen;
                case ScreenType::combat_reward: return combat_reward_screen;
                default:return nullptr;
            }
        }
    };
}
#endif