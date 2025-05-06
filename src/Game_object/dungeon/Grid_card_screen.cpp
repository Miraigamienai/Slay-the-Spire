#include <utility>

#include "Game_object/dungeon/Grid_card_screen.hpp"
#include "Game_object/card/Card_group.hpp"
#include "Game_object/card/Cards.hpp"

namespace Dungeon{
    Grid_card_screen::Grid_card_screen(){
        
    }

    void Grid_card_screen::open(const Card::Card_group &display_group){
        this->display_group=display_group;
    }

    void Grid_card_screen::open(Card::Card_group &&display_group){
        this->display_group=std::move(display_group);
    }

    void Grid_card_screen::update_cards(){
        for(size_t i=0;i<display_group.size();++i){
            
        }
    }
}