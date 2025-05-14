#pragma once
//how to do????
#include <utility>
#include <memory>
#include <type_traits>

#include "Game_object/interface/Is_screen.hpp"
#include "Game_object/card/Card_group.hpp"
#include "Game_object/button/Cancel_button.hpp"
#include "RUtil/Scroll.hpp"

//fwd decl
namespace Dungeon{
    struct Dungeon_shared;
    namespace GridScreenAction{
        class Grid_screen_action;
    }
}
namespace Card{
    class Cards;
}

namespace Dungeon{
//need cards,buttons,???
//smith: cancel and confirm button and upgraded card? //need to do in other class?
class Grid_card_screen final:public Interface::Is_screen
{
public:
    Grid_card_screen();
    ~Grid_card_screen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    
    template <typename T>
    using CardGroupOnlyVoid = std::enable_if_t<std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, Card::Card_group>, void>;

    template <typename T>
    CardGroupOnlyVoid<T> open(T&&display_group, const std::shared_ptr<GridScreenAction::Grid_screen_action> &screen_action){
        if constexpr(std::is_rvalue_reference_v<T&&>){
            this->display_group=std::move(display_group);
        }else{
            for(const auto&it:display_group)
                this->display_group.AddTop(it);
        }
        this->screen_action=screen_action;
        common_open_setting();
    }

    template <typename T>
    CardGroupOnlyVoid<T> open(T&&display_group, const std::shared_ptr<GridScreenAction::Grid_screen_action> &screen_action, bool&is_done, bool&is_cancelled){
        open(std::forward<T>(display_group), screen_action);
        is_done = is_cancelled =false;
        this->out_is_done=&is_done;
        this->out_is_cancelled=&is_cancelled;
    }

private:
    Card::Card_group display_group;
    std::shared_ptr<Card::Cards> hovered_card;
    float offset_y, target_offset_y;
    float draw_start_y;
    RUtil::Scroll scroll;
    bool is_confirming;
    std::shared_ptr<GridScreenAction::Grid_screen_action> screen_action;
    bool *out_is_done, *out_is_cancelled;
    float cancel_display_timer;
    Button::Cancel_button cancel;
    bool closing;

    void update_cards(Dungeon_shared &dungeon_shared);
    void common_open_setting();
    void set_cards_position_when_opening();
    static constexpr int N=5;
    static constexpr float DISPLAY_TIME=0.75F;
};
}