#ifndef GAME_OBJECT_DUNGEON_DUNGEON_MANAGER
#define GAME_OBJECT_DUNGEON_DUNGEON_MANAGER

#include <utility>

#include "Game_object/dungeon/Dungeon_screen.hpp"
#include "Game_object/dungeon/Combat_reward_screen.hpp"
#include "Game_object/dungeon/Grid_card_screen.hpp"
#include "Game_object/dungeon/Shop_screen.hpp"
#include "Game_object/dungeon/Death_screen.hpp"
#include "Game_object/dungeon/Discard_pile_screen.hpp"
#include "Game_object/dungeon/Draw_pile_screen.hpp"
#include "Game_object/map/Map_node.hpp"
#include "Game_object/top_panel/Top_panel.hpp"
#include "Game_object/dungeon/Victory_screen.hpp"

namespace Dungeon{
    //This class will auto change where need to update or render.
    class Dungeon_manager
    {
    public:
        Dungeon_manager();
        ~Dungeon_manager()=default;
        void update(Dungeon_shared &dungeon_shared);
        void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
        template <typename...Args>
        void set_display_map(Args&&...args)const{m_dungeon_screen->set_display_map(std::forward<Args>(args)...);}
        void set_current_on_top(bool value)const{current_screen->set_on_top(value);}
        void hide_dungeon_screen_instantly(){m_dungeon_screen->hide_instantly();last_screen=m_dungeon_screen;current_screen=nullptr;}
        void set_current_none()noexcept{current_screen->set_on_top(false);current_screen=nullptr;}
        void back_to_last_screen()noexcept{current_screen->set_on_top(false);std::swap(current_screen,last_screen);if(current_screen!=nullptr)current_screen->set_on_top(true);}
        bool current_screen_equals(Abstraction::ScreenType ST)const noexcept{return ST==Abstraction::ScreenType::NONE ? current_screen==nullptr : current_screen!=nullptr&&current_screen->type==ST;}
        bool DeathBackToInitScreen()const noexcept(noexcept(death_screen->BackToInitScreen())){return current_screen!=nullptr&&current_screen->type==Abstraction::ScreenType::death && death_screen->BackToInitScreen();}
        bool VictoryBackToInitScreen()const noexcept(noexcept(victory_screen->BackToInitScreen())){return current_screen!=nullptr&&current_screen->type==Abstraction::ScreenType::victory && victory_screen->BackToInitScreen();}
        bool boss_click()const noexcept(noexcept(m_dungeon_screen->boss_click())){return m_dungeon_screen->boss_click();}
        template <Abstraction::ScreenType ST, typename ...Args>
        void open(Args&&...args){
            if(current_screen!=nullptr) current_screen->set_on_top(false);
            last_screen=current_screen;
            if constexpr (ST==Abstraction::ScreenType::NONE){
                current_screen=nullptr;
            }else{
                current_screen=GetScreen<ST>();
                if(last_screen==current_screen) last_screen=nullptr;
                current_screen->set_on_top(true);
                GetScreen<ST>()->open(std::forward<Args>(args)...);
            }
        }
        void reset()noexcept{
            current_screen=nullptr;
            last_screen=nullptr;
        }
    private:
        std::shared_ptr<Abstraction::Is_screen> current_screen=nullptr,last_screen=nullptr;
        std::shared_ptr<Dungeon::Dungeon_screen> m_dungeon_screen;
        std::shared_ptr<Dungeon::Combat_reward_screen> combat_reward_screen;
        std::shared_ptr<Dungeon::Grid_card_screen> grid_card_screen;
        std::shared_ptr<Dungeon::Shop_screen> shop_screen;
        std::shared_ptr<Dungeon::Death_screen> death_screen;
        std::shared_ptr<TopPanel::Top_panel> top_panel;
        std::shared_ptr<Dungeon::Victory_screen> victory_screen;
        std::shared_ptr<Dungeon::Discard_pile_screen> discard_pile_screen;
        std::shared_ptr<Dungeon::Draw_pile_screen> draw_pile_screen;
        
        template <Abstraction::ScreenType ST>
        const auto &GetScreen()const{
            if constexpr(ST==Abstraction::ScreenType::main_dungeon) return m_dungeon_screen;
            else if constexpr(ST==Abstraction::ScreenType::combat_reward) return combat_reward_screen;
            else if constexpr(ST==Abstraction::ScreenType::grid_cards) return grid_card_screen;
            else if constexpr(ST==Abstraction::ScreenType::shop) return shop_screen;
            else if constexpr(ST==Abstraction::ScreenType::death) return death_screen;
            else if constexpr(ST==Abstraction::ScreenType::victory) return victory_screen;
            else if constexpr(ST==Abstraction::ScreenType::discard_pile) return discard_pile_screen;
            else if constexpr(ST==Abstraction::ScreenType::draw_pile) return draw_pile_screen;
        }
    };
}
#endif