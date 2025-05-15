#include "Game_object/dungeon/Grid_card_screen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/dungeon/Grid_screen_action/Grid_screen_action.hpp"
#include "Game_object/card/Card_group.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/character/Player.hpp"
#include "RUtil/Random.hpp"
#include "WindowSize.hpp"

#include "Util/Logger.hpp"

namespace Dungeon{
    constexpr float PAD=40.0F*Setting::SCALE;
    constexpr float DRAW_START_X=(static_cast<float>(Setting::WINDOW_WIDTH)//total
                                -5.0F*Card::Cards::IMG_WIDTH*0.75F - 4.0F*PAD)//non space size
                                /2.0F//half non space size
                                +Card::Cards::IMG_WIDTH*0.75F/2.0F;//to card middle
    constexpr float CARD_PAD_X=PAD+Card::Cards::IMG_WIDTH*0.75F;
    constexpr float CARD_PAD_Y=PAD+Card::Cards::IMG_HEIGHT*0.75F;
    constexpr float DEFAULT_SCROLL_BOUND=Setting::SCALE*50.0F;
 
    Grid_card_screen::Grid_card_screen()
        :Interface::Is_screen(Interface::ScreenType::grid_cards),
        hovered_card(nullptr),
        offset_y(0.0F),
        target_offset_y(0.0F),
        draw_start_y(0.0F),
        scroll(offset_y, target_offset_y, -DEFAULT_SCROLL_BOUND, DEFAULT_SCROLL_BOUND),
        is_confirming(false),
        out_is_done(nullptr),
        out_is_cancelled(nullptr),
        closing(false)
    {
        
    }

    void Grid_card_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(!on_top&&closing){
            cancel.update();
            return;
        }
        if(!is_confirming){
            //cancel timer update
            if(cancel_display_timer!=0.0F){
                cancel_display_timer-=RUtil::Game_Input::delta_time();
                if(cancel_display_timer<0.0F){
                    cancel_display_timer=0.0F;
                    cancel.show();
                }
            }
            //cards update first
            update_cards(dungeon_shared);
            //cancel update
            this->cancel.update();
            if(out_is_cancelled!=nullptr&&on_top){
                if(this->cancel.is_logically_clicked()){
                    *out_is_cancelled=true;
                    closing=true;
                    cancel.hide();
                    dungeon_shared.manager.back_to_last_screen();
                    return;
                }
            }
            //scroll
            scroll.update();
            //check the hovered card
            if(hovered_card!=nullptr&&on_top){
                hovered_card->Hover();
                //check if clicked
                if(hovered_card->HitboxClicked()){
                    if(screen_action==nullptr){
                        LOG_ERROR("screen_action is nullptr in Grid_card_screen.cpp");
                    }else{
                        is_confirming=true;
                        screen_action->SetCard(this->hovered_card);
                        this->cancel.hide(screen_action->have_cancel_button);
                    }
                }
            }
        }else{
            screen_action->update(dungeon_shared);
            if(screen_action->IsCancelled()){
                is_confirming=false;
                if(screen_action->have_cancel_button)//show after display time
                    this->cancel_display_timer=Button::Cancel_button::DISPLAY_TIME;
                else//immediately show if doen't have cancel button in action
                    this->cancel.show();
            }else if(screen_action->IsDone()){
                if(out_is_done!=nullptr) *out_is_done=true;
                this->display_group.clear();
                this->cancel.hide(true);//hide immediately
                dungeon_shared.manager.back_to_last_screen();
                closing=true;
            }
        }
    }
    
    void Grid_card_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(!on_top&&closing){
            this->cancel.render(r2);
            return;
        }
        if(hovered_card!=nullptr){
            //for ensure the hovered card is on top.
            for(const auto&it:display_group) 
                if(it!=hovered_card)
                    it->render(r2);
            hovered_card->render_hovered_shadow(r2);
            hovered_card->render(r2);
        }else{
            display_group.render(r2);
        }
        this->cancel.render(r2);
        if(is_confirming){
            screen_action->render(r2);
        }
    }
    
    void Grid_card_screen::common_open_setting(){
        draw_start_y=static_cast<float>(Setting::WINDOW_HEIGHT) * (display_group.size()<=N?0.5F:0.66F);
        offset_y = target_offset_y = 0.0F;
        set_cards_position_when_opening();
        //set scroll bound
        const int scroll_y=display_group.size() <= 2*N ? DEFAULT_SCROLL_BOUND : DEFAULT_SCROLL_BOUND+CARD_PAD_Y*((display_group.size()+N-1)/N - 2);
        this->scroll.ChangeBiggerBound(scroll_y);
        cancel.show();
        this->out_is_done=nullptr;
        this->out_is_cancelled=nullptr;
        is_confirming=false;
        closing=false;
    }

    void Grid_card_screen::update_cards(Dungeon_shared &dungeon_shared){
        hovered_card=nullptr;
        int now_y=0;
        int now_x=0;
        for(const auto&it:display_group){
            it->SetX(DRAW_START_X+ static_cast<float>(now_x)*CARD_PAD_X);
            it->SetY(draw_start_y+ offset_y - static_cast<float>(now_y)*CARD_PAD_Y);
            it->update(dungeon_shared.top_effs);
            if(it->HitboxHovered()) hovered_card=it;
            else it->Unhover();
            
            ++now_x;
            if(now_x>=N){
                now_x=0;
                ++now_y;
            }
        }
    }

    void Grid_card_screen::set_cards_position_when_opening(){
        int now_y=0;
        int now_x=0;
        for(const auto&it:display_group){
            it->SetAngle(0.0F, true);
            it->SetX(DRAW_START_X+ static_cast<float>(now_x)*CARD_PAD_X + RUtil::Random::GetRandomFloat(-100.0F, 100.0F)*Setting::SCALE, true);
            it->SetY(draw_start_y+ offset_y - static_cast<float>(now_y)*CARD_PAD_Y - RUtil::Random::GetRandomFloat(100.0F, 200.0F)*Setting::SCALE, true);
            it->SetDrawScale(0.75F, true);
            if(it->HitboxHovered()) hovered_card=it;
            
            ++now_x;
            if(now_x>=N){
                now_x=0;
                ++now_y;
            }
        }
    }

}