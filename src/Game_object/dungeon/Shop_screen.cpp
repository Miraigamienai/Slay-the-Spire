#include "Game_object/dungeon/Shop_screen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/card/Cards.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Draw_2D.hpp"

namespace Dungeon{
    Shop_screen::Shop_screen()
        :Interface::Is_screen(Interface::ScreenType::shop),
        current_y(Setting::WINDOW_HEIGHT),
        hand_timer(0.0F),
        hand_x(0.0F),
        hand_target_x(0.0F),
        hand_y(0.0F),
        hand_target_y(0.0F)
    {
        
    }
    
    void Shop_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        //current_y update
        if(current_y!=0.0F)
            current_y=RUtil::Math::varlerp(current_y, 0.0F, 5.0F, Setting::SCALE);
        //hand update
        hand_update();
        //cards update
        cards_update(dungeon_shared.top_effs);
    }
    
    void Shop_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::WHITE);
        // r2->draw()
    }

    void Shop_screen::hand_update(){
        if(hand_timer>0.0F){
            hand_timer-=RUtil::Game_Input::delta_time();
        }else{
            hand_x=RUtil::Math::Apply(hand_x, hand_target_x, RUtil::Game_Input::delta_time()*6.0F);
            if(hand_y>hand_target_y)//up to down
                hand_y=RUtil::Math::Apply(hand_y, hand_target_y, RUtil::Game_Input::delta_time()*6.0F);
            else //down to up
                hand_y=RUtil::Math::Apply(hand_y, hand_target_y, RUtil::Game_Input::delta_time()*1.5F);
        }
    }

    void Shop_screen::cards_update(Effect::Effect_group &top_effs)const{
        for(decltype(card1.size()) i=0;i<card1.size();i++){
            card1[i]->SetY(this->current_y + TOP_ROW_Y, true);
            card1[i]->update(top_effs);
        }
        for(decltype(card2.size()) i=0;i<card2.size();i++){
            card2[i]->SetY(this->current_y + BOTTOM_ROW_Y, true);
            card2[i]->update(top_effs);
        }
    }
}