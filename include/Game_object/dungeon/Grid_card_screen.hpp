//how to do????
#include <utility>
#include <memory>

#include "Game_object/interface/Is_screen.hpp"
#include "Game_object/card/Card_group.hpp"
#include "RUtil/Scroll.hpp"

//fwd decl
namespace Dungeon{
    class Dungeon_shared;
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
    void open(const Card::Card_group &display_group, const std::shared_ptr<GridScreenAction::Grid_screen_action> &screen_action){
        for(const auto&it:display_group)
            this->display_group.AddTop(it);
        common_open_setting(screen_action);
    }
    void open(Card::Card_group &&display_group, const std::shared_ptr<GridScreenAction::Grid_screen_action> &screen_action){
        this->display_group=std::move(display_group);
        common_open_setting(screen_action);
    }
private:
    Card::Card_group display_group;
    std::shared_ptr<Card::Cards> hovered_card;
    float offset_y, target_offset_y;
    float draw_start_y;
    RUtil::Scroll scroll;
    bool is_confirming;
    std::shared_ptr<GridScreenAction::Grid_screen_action> screen_action;

    void update_cards(Dungeon_shared &dungeon_shared);
    void common_open_setting( const std::shared_ptr<GridScreenAction::Grid_screen_action> &screen_action);
    void set_cards_position_when_opening();
    static constexpr int N=5;
};
}