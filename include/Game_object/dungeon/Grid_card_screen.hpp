//how to do????
#include "Game_object/interface/Is_screen.hpp"

namespace Dungeon{
//need cards,buttons,???
//smith: cancel and confirm button and upgraded card? //need to do in other class?
class Grid_card_screen final:public Interface::Is_screen
{
public:
    Grid_card_screen();
    ~Grid_card_screen()override=default;
    void open(const Card::Card_group &display_group);
    void open(Card::Card_group &&display_group);
private:
    Card::Card_group display_group;
    float offset_y;
    void update_cards();
};
}