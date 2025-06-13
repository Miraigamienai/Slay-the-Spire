#include "Game_object/card/Card_group_handler.hpp"//the hpp
#include "Game_object/character/Monster/Monsters.hpp"//hovered monster
#include "Game_object/character/Monster_group.hpp"//monsters hover check
#include "Game_object/action/Action_group_handler.hpp"//for using card
#include "Game_object/dungeon/Dungeon_shared.hpp"//get player inside this struct
#include "RUtil/Random.hpp"//rng
#include "RUtil/Game_Input.hpp"//cursor input and delta_time
#include "RUtil/Some_Math.hpp"//Bezier method
#include "RUtil/Image_book.hpp"//loading img
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"//for rendering
#include "Cursor.hpp"//for hiding or displaying cursor

#include "Util/Logger.hpp"//LOG_ERROR

namespace Card{
    static constexpr float LOW_LOW_LINE=50.0F*Setting::SCALE;
    static constexpr float HOVER_CARD_Y_POSITION=210.0F*Setting::SCALE;
    static constexpr float START_LINE_OFFSET=140.0F*Setting::SCALE;
    static constexpr float CARD_DROP_END_Y=static_cast<float>(Setting::WINDOW_HEIGHT)*0.81F;
    static constexpr float CARD_DROP_START_Y=350.0F*Setting::SCALE;

    Card_group_handler::Card_group_handler(){
        single_target=pass_hesitation_line=is_dragging_card=false;
        m_arrow_timer=0.0F;
        arrow_scale=Setting::SCALE;
        //in_drop_zone:(x,y) in area that can use card.  //This is ok without init.
        //is_dragging_card: dragging card,include in single_target mode
        //single_target: targeting one enemy
        //pass_hesitation_line: dragging card to in_drop_zone
    }

    void Card_group_handler::shuffle(bool shuffle_invisible){
        //remember to shuffle the order of m_discard before this function be called.
        if(m_discard.empty()) LOG_ERROR("Try to shuffle card when the m_discard is empty.");
        else{
            auto card=m_discard.PopTop();
            card->Darken(true);
            card->Shrink(true);
            card->StopGlowing();
            card->shuffle(shuffle_invisible);
            flying_cards.emplace_back(card);
            draw_pile.AddTop(card);
        }
    }

    void Card_group_handler::draw(const Power::Power_group &player_powers){
        //to hand, don't need to add to flying card list.
        if(draw_pile.empty()){
            LOG_ERROR("the draw_pile is empty, but it was drawn.");
        }else{
            auto card=draw_pile.PopTop();
            card->draw();
            card->SetHoverTimer(0.0F);
            card->RefreshDisplay(player_powers);
            hand_cards.AddTop(card);
            refresh_hand_layout();
        }
    }

    void Card_group_handler::discard_all(){
        for(const auto&it:hand_cards){
            it->Shrink(false);
            it->Darken(false);
            it->StopGlowing();
            it->discard();
            flying_cards.emplace_back(it);
        }
        hand_cards.MoveAllCardTo(m_discard);
    }

    void Card_group_handler::discard(const std::shared_ptr<Cards> &card, bool visual_only){
        card->Shrink(false);
        card->Darken(false);
        card->StopGlowing();
        card->discard();
        flying_cards.emplace_back(card);
        if(!visual_only)
            this->m_discard.AddTop(card);
    }

    void Card_group_handler::to_draw_pile(const std::shared_ptr<Cards> &card){
        card->Shrink(false);
        card->Lighten(true);
        card->StopGlowing();
        card->to_draw_pile();
        flying_cards.emplace_back(card);
    }
    
    void Card_group_handler::obtain(const std::shared_ptr<Cards> &card){
        card->Shrink(false);
        card->obtain();
        flying_cards.emplace_back(card);
        this->master_deck.AddTop(card);
    }

    void Card_group_handler::exhaust(const std::shared_ptr<Cards> &card){
        this->exhaust_pile.AddTop(card);
        card->StopGlowing();
    }

    void Card_group_handler::empower(const std::shared_ptr<Cards> &card, float target_center_x, float target_center_y){
        card->Shrink(false);
        card->empower(target_center_x, target_center_y);
        flying_cards.emplace_back(card);
    }

    void Card_group_handler::release_card(){
        single_target=false;
        pass_hesitation_line=false;
        is_dragging_card=false;

        if(hovered_card!=nullptr){
            //hovertimer
            hovered_card->SetHoverTimer(0.25F);
            hovered_card->Unhover();
        }
        hovered_card=nullptr;
        refresh_hand_layout();
        
    }

    void Card_group_handler::play_card(Action::Action_group_handler &action_group_handler){
        if(!hovered_card->CanUse()){
            release_card();
            return;
        }
        //this function will not remove the card from hand_cards.It only sends the card to action_group_handler.
        hovered_card->SetCanHoverInHand(false);
        hovered_card->Unhover();
        if(hovered_card->IsSingleTarget())
            action_group_handler.AddCardQueue(Card_item{hovered_card,hovered_monster});
        else
            action_group_handler.AddCardQueue(Card_item{hovered_card,nullptr});
        hovered_card=nullptr;
        is_dragging_card=false;
    }

    void Card_group_handler::refresh_hand_layout()const{
        const int len=hand_cards.size();
        if(len==0) return;
        const float angle_start=(float)len*INCREMENT_ANGLE/2.0F,
                    increment_sink=SINK_RANGE/(float)len/2.0F;
        const int middle=len/2;
        for(int i=0;i<len;i++){
            //len=4         //len=3
            //middle=2      //middle=1
            //0 1 2 3       //0 1 2
            //-2 -1 0 1     //-1 0 1
            //-1 0 0 -1
            //set y
            int t = i - middle;
            if(0<=t)t=-t;
            else if(!bool(len&1))t++;
            t=(int)((float)t*1.7F);
            hand_cards[i]->SetY(SINK_START+increment_sink*t);
            //set angle
            hand_cards[i]->SetAngle(angle_start-((float)i+0.5F)*INCREMENT_ANGLE);
        }
        //adjust y & set x
        constexpr float half_width=(float)Setting::WINDOW_WIDTH/2.0F;
        switch (len)
        {
        case 1:
            hand_cards[0]->SetX(half_width);
            break;
        case 2:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*0.47F);
            hand_cards[1]->SetX(half_width+Cards::IMG_WIDTH_S*0.53F);
            break;
        case 3:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*0.9F);
            hand_cards[1]->SetX(half_width);
            hand_cards[2]->SetX(half_width+Cards::IMG_WIDTH_S*0.9F);
            hand_cards[0]->MoveTargetY(20.0F*Setting::SCALE);
            hand_cards[2]->MoveTargetY(20.0F*Setting::SCALE);
            break;
        case 4:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*1.36F);
            hand_cards[1]->SetX(half_width-Cards::IMG_WIDTH_S*0.46F);
            hand_cards[2]->SetX(half_width+Cards::IMG_WIDTH_S*0.46F);
            hand_cards[3]->SetX(half_width+Cards::IMG_WIDTH_S*1.36F);
            hand_cards[1]->MoveTargetY(-10.0F*Setting::SCALE);
            hand_cards[2]->MoveTargetY(-10.0F*Setting::SCALE);
            break;
        case 5:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*1.7F);
            hand_cards[1]->SetX(half_width-Cards::IMG_WIDTH_S*0.9F);
            hand_cards[2]->SetX(half_width);
            hand_cards[3]->SetX(half_width+Cards::IMG_WIDTH_S*0.9F);
            hand_cards[4]->SetX(half_width+Cards::IMG_WIDTH_S*1.7F);
            hand_cards[0]->MoveTargetY(25.0F*Setting::SCALE);
            hand_cards[2]->MoveTargetY(-10.0F*Setting::SCALE);
            hand_cards[4]->MoveTargetY(25.0F*Setting::SCALE);
            break;
        case 6:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*2.1F);
            hand_cards[1]->SetX(half_width-Cards::IMG_WIDTH_S*1.3F);
            hand_cards[2]->SetX(half_width-Cards::IMG_WIDTH_S*0.43F);
            hand_cards[3]->SetX(half_width+Cards::IMG_WIDTH_S*0.43F);
            hand_cards[4]->SetX(half_width+Cards::IMG_WIDTH_S*1.3F);
            hand_cards[5]->SetX(half_width+Cards::IMG_WIDTH_S*2.1F);
            hand_cards[0]->MoveTargetY(10.0F*Setting::SCALE);
            hand_cards[5]->MoveTargetY(10.0F*Setting::SCALE);
            break;
        case 7:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*2.4F);
            hand_cards[1]->SetX(half_width-Cards::IMG_WIDTH_S*1.7F);
            hand_cards[2]->SetX(half_width-Cards::IMG_WIDTH_S*0.9F);
            hand_cards[3]->SetX(half_width);
            hand_cards[4]->SetX(half_width+Cards::IMG_WIDTH_S*0.9F);
            hand_cards[5]->SetX(half_width+Cards::IMG_WIDTH_S*1.7F);
            hand_cards[6]->SetX(half_width+Cards::IMG_WIDTH_S*2.4F);
            hand_cards[0]->MoveTargetY(25.0F*Setting::SCALE);
            hand_cards[1]->MoveTargetY(18.0F*Setting::SCALE);
            hand_cards[3]->MoveTargetY(-6.0F*Setting::SCALE);
            hand_cards[5]->MoveTargetY(18.0F*Setting::SCALE);
            hand_cards[6]->MoveTargetY(25.0F*Setting::SCALE);
            break;
        case 8:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*2.5F);
            hand_cards[1]->SetX(half_width-Cards::IMG_WIDTH_S*1.82F);
            hand_cards[2]->SetX(half_width-Cards::IMG_WIDTH_S*1.1F);
            hand_cards[3]->SetX(half_width-Cards::IMG_WIDTH_S*0.38F);
            hand_cards[4]->SetX(half_width+Cards::IMG_WIDTH_S*0.38F);
            hand_cards[5]->SetX(half_width+Cards::IMG_WIDTH_S*1.1F);
            hand_cards[6]->SetX(half_width+Cards::IMG_WIDTH_S*1.77F);
            hand_cards[7]->SetX(half_width+Cards::IMG_WIDTH_S*2.5F);
            hand_cards[1]->MoveTargetY(10.0F*Setting::SCALE);
            hand_cards[6]->MoveTargetY(10.0F*Setting::SCALE);
            for(const auto&it:hand_cards) it->SetDrawScale(0.7125F);
            break;
        case 9:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*2.8F);
            hand_cards[1]->SetX(half_width-Cards::IMG_WIDTH_S*2.2F);
            hand_cards[2]->SetX(half_width-Cards::IMG_WIDTH_S*1.53F);
            hand_cards[3]->SetX(half_width-Cards::IMG_WIDTH_S*0.8F);
            hand_cards[4]->SetX(half_width);
            hand_cards[5]->SetX(half_width+Cards::IMG_WIDTH_S*0.8F);
            hand_cards[6]->SetX(half_width+Cards::IMG_WIDTH_S*1.53F);
            hand_cards[7]->SetX(half_width+Cards::IMG_WIDTH_S*2.2F);
            hand_cards[8]->SetX(half_width+Cards::IMG_WIDTH_S*2.8F);
            hand_cards[1]->MoveTargetY(22.0F*Setting::SCALE);
            hand_cards[2]->MoveTargetY(18.0F*Setting::SCALE);
            hand_cards[3]->MoveTargetY(12.0F*Setting::SCALE);
            hand_cards[5]->MoveTargetY(12.0F*Setting::SCALE);
            hand_cards[6]->MoveTargetY(18.0F*Setting::SCALE);
            hand_cards[7]->MoveTargetY(22.0F*Setting::SCALE);
            for(const auto&it:hand_cards) it->SetDrawScale(0.67499995F);
            break;
        case 10:
            hand_cards[0]->SetX(half_width-Cards::IMG_WIDTH_S*2.9F);
            hand_cards[1]->SetX(half_width-Cards::IMG_WIDTH_S*2.4F);
            hand_cards[2]->SetX(half_width-Cards::IMG_WIDTH_S*1.8F);
            hand_cards[3]->SetX(half_width-Cards::IMG_WIDTH_S*1.1F);
            hand_cards[4]->SetX(half_width-Cards::IMG_WIDTH_S*0.4F);
            hand_cards[5]->SetX(half_width+Cards::IMG_WIDTH_S*0.4F);
            hand_cards[6]->SetX(half_width+Cards::IMG_WIDTH_S*1.1F);
            hand_cards[7]->SetX(half_width+Cards::IMG_WIDTH_S*1.8F);
            hand_cards[8]->SetX(half_width+Cards::IMG_WIDTH_S*2.4F);
            hand_cards[9]->SetX(half_width+Cards::IMG_WIDTH_S*2.9F);
            hand_cards[1]->MoveTargetY(20.0F*Setting::SCALE);
            hand_cards[2]->MoveTargetY(17.0F*Setting::SCALE);
            hand_cards[3]->MoveTargetY(12.0F*Setting::SCALE);
            hand_cards[4]->MoveTargetY(5.0F*Setting::SCALE);
            hand_cards[5]->MoveTargetY(5.0F*Setting::SCALE);
            hand_cards[6]->MoveTargetY(12.0F*Setting::SCALE);
            hand_cards[7]->MoveTargetY(17.0F*Setting::SCALE);
            hand_cards[8]->MoveTargetY(20.0F*Setting::SCALE);
            for(const auto&it:hand_cards) it->SetDrawScale(0.63750005F);
            break;
        default:
            LOG_ERROR("There are too many cards in hand.");
            break;
        }
        //adjust scale
        if(len<8){
            for(const auto&it:hand_cards) it->SetDrawScale(0.75F);
        }
        //if hovered card
        if(hovered_card!=nullptr){
            hovered_card->SetAngle(0.0F, true);
            hovered_card->SetX(hovered_card->GetX(), true);
            hovered_card->SetY(hovered_card->GetY(), true);
        }
    }
    
    void Card_group_handler::update(Dungeon::Dungeon_shared &dungeon_shared){
        //single_target -> drop zone -> drag -> hover -> check drag start
        if(single_target){
            bool last_has_not=hovered_monster==nullptr;
            hovered_monster=dungeon_shared.room_monsters.GetBodyHoveredMonster();
            if(last_has_not && hovered_monster!=nullptr){
                hovered_card->RefreshDisplay(dungeon_shared.player->get_powers(), hovered_monster->get_powers());
            }else if(!last_has_not && hovered_monster==nullptr){
                hovered_card->RefreshDisplay(dungeon_shared.player->get_powers());
            }
            this->update_targeting(dungeon_shared);
            return;
        }

        if(is_dragging_card){//is_dragging_card==true only if (hovered_card!=nullptr)
            this->update_drop_zone_status();
            if(is_dragging_card){//if is_dragging_card after update_drop_zone_status();
                this->handle_dragging(dungeon_shared.action_group_handler);
                if(single_target)
                    return;
            }
        }

        //check hover card
        this->update_hovered_card();
        
        //check drag start
        if(hovered_card!=nullptr)
            this->check_drag_start();
    }

    void Card_group_handler::check_drag_start(){
        if(just_l&&!this->is_dragging_card){
            this->hover_start_line=(float)input_y+START_LINE_OFFSET;
            this->is_dragging_card=true;
            this->pass_hesitation_line=false;
            this->hovered_card->SetDrawScale(0.7F);
        }
    }

    void Card_group_handler::update_hovered_card(){
        if(hovered_card==nullptr){
            hovered_card=hand_cards.GetHoveredCard();
            if(hovered_card!=nullptr){
                hovered_card->SetY(HOVER_CARD_Y_POSITION,true);
                hovered_card->SetAngle(0.0F);
                hovered_card->Hover();
                this->hand_card_push();
            }
        }else if(!is_dragging_card&&!hovered_card->IsHoveredInHand(1.0F)){
            this->release_card();
        }
    }

    void Card_group_handler::update_drop_zone_status(){
        const bool last_in=in_drop_zone;
        in_drop_zone=CARD_DROP_START_Y<(float)input_y&&(float)input_y<CARD_DROP_END_Y;
        if(!last_in&&in_drop_zone){//first in
            hovered_card->Flash(0x87ceeb00);//color.sky
        }
        if(in_drop_zone){//in_drop_zone is false not equel pass_hesitation_line is false.
            pass_hesitation_line=true;
        }
        if((float)input_y<LOW_LOW_LINE&&pass_hesitation_line){//If this is true, then in_drop_zone must be false.
            pass_hesitation_line=false;
            this->release_card();
        }
    }

    void Card_group_handler::handle_dragging(Action::Action_group_handler &action_group_handler){
        if(just_r){
            release_card();
            return;
        }

        if(in_drop_zone&&hovered_card->IsSingleTarget()){//start single target
            if(just_l){//but if just_l cancle the start and release card.
                release_card();
            }else{
                single_target=true;
                arrowX=input_x;
                arrowY=input_y;
                Cursor::SetVisible(false);
                refresh_hand_layout();
                hovered_card->SetX(Setting::WINDOW_WIDTH/2.0F);
                hovered_card->SetY(Card::Cards::IMG_HEIGHT*0.75F/2.5F);
                hovered_card->SetAngle(0.0F);
            }
            return;
        }

        if(just_l&&in_drop_zone){//trigger the card
            this->play_card(action_group_handler);
            is_dragging_card=false;
            pass_hesitation_line=false;//just in case
            return;
        }

        //just move the card to cursor.
        hovered_card->SetX(input_x);
        hovered_card->SetY(input_y);
    }
    
    void Card_group_handler::prepare_for_battle(RUtil::Random &rng){
        this->m_discard.clear();
        this->hand_cards.clear();
        this->exhaust_pile.clear();
        this->draw_pile.CloneOther(this->master_deck);
        draw_pile.ShuffleWithRng(rng);
        hovered_card=nullptr;
        single_target=pass_hesitation_line=is_dragging_card=false;
        hovered_monster=nullptr;
    }
    void Card_group_handler::render_hand(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(hovered_card!=nullptr){
            //for ensure the hovered card is on top.
            for(const auto&it:hand_cards) 
                if(it!=hovered_card)
                    it->render(r2);
            hovered_card->render_hovered_shadow(r2);
            hovered_card->render(r2);
        }else{
            hand_cards.render(r2);
        }

        this->render_flying_cards(r2);//may need to check.

        if(single_target)
            render_targeting(r2);
    }

    void Card_group_handler::update_hand_cards(Effect::Effect_group &top_effs, const Dungeon::Dungeon_shared &dungeon_shared){
        hand_cards.update(top_effs);
        for(const auto&it:hand_cards)it->CanUseUpdate(dungeon_shared);
        update_force_cards(top_effs);
    }

    void Card_group_handler::render_targeting(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(hovered_monster==nullptr){
            r2->SetColor(-1);
        }else{
            r2->SetColor(ARROW_COLOR,1.0F);
        }
        //control point
        const float cp_x=hovered_card->GetX()-(arrowX-hovered_card->GetX())/4.0F,
                    cp_y=arrowY+(arrowY-hovered_card->GetY())/2.0F;
        const glm::vec2 ctr_pt{cp_x,cp_y};
        //hover -> arrow
        const glm::vec2 start{hovered_card->GetX(),hovered_card->GetY()},end{arrowX,arrowY};
        float rad=7.0F*Setting::SCALE;
        glm::vec2 last_pt,now_pt{ctr_pt};
        const float step=1.0F/20.0F;
        for(int i=0;i<19;i++){//draw block
            rad+=0.4F*Setting::SCALE;
            last_pt=now_pt;
            now_pt=RUtil::Math::BezierQuadratic(start,ctr_pt,end,(float)i*step);
            r2->draw(reticleBlock_img, now_pt.x-64.0F, now_pt.y-64.0F, 128.0F, 128.0F, RUtil::Math::GetDegress(now_pt-last_pt)+(i==0?90.0F:-90.0F), 64.0F, 64.0F, rad/18.0F, rad/18.0F);
        }
        last_pt=now_pt;
        now_pt=end;
        //draw arrow
        r2->draw(reticleArrow_img, arrowX-128.0F, arrowY-128.0F, 256.0F, 256.0F, RUtil::Math::GetDegress(now_pt-last_pt)-90.0F, 128.0F, 128.0F, arrow_scale, arrow_scale);
    }
    void Card_group_handler::update_targeting(Dungeon::Dungeon_shared &dungeon_shared){
        if(hovered_monster!=nullptr){
            m_arrow_timer+=RUtil::Game_Input::delta_time();
            if(m_arrow_timer>1.0F){
                m_arrow_timer=1.0F;
                arrow_scale=1.2F*Setting::SCALE;
            }else{
                arrow_scale=RUtil::Math::Apply(Setting::SCALE,1.2F*Setting::SCALE,RUtil::Math::interpolation_elastic_out(m_arrow_timer));
            }
        }else{
            m_arrow_timer=0.0F;
            arrow_scale=Setting::SCALE;
        }

        if(just_r||(float)input_y<LOW_LOW_LINE||(float)input_y<hover_start_line - 400.0F*Setting::SCALE){//release if height is not in range.
            hovered_card->RefreshDisplay(dungeon_shared.player->get_powers());
            release_card();
            single_target=false;
            Cursor::SetVisible(true);
            hovered_monster=nullptr;
            return;
        }

        if(just_l){
            if(hovered_monster!=nullptr){
                single_target=false;
                Cursor::SetVisible(true);
                play_card(dungeon_shared.action_group_handler);
                hovered_monster=nullptr;
            }
            return;
        }

        arrowX=RUtil::Math::varlerp(arrowX,(float)input_x,20.0F,UI_THRESHOLD);
        arrowY=RUtil::Math::varlerp(arrowY,(float)input_y,20.0F,UI_THRESHOLD);
    }

    void Card_group_handler::hand_card_push()const{
        const int len=hand_cards.size();
        if(len>1){
            const int pos=hand_cards.GetCardPos(hovered_card);
            if(pos!=-1){
                const float push=len==2?0.2F:(len==3||len==4?0.27F:0.4F);
                float j=push;
                //right
                for(int i=pos+1;i<len;i++){
                    hand_cards[i]->MoveTargetX(Cards::IMG_WIDTH_S*j);
                    j*=0.25F;
                }
                j=push;
                //left
                for(int i=pos-1;0<=i;i--){
                    hand_cards[i]->MoveTargetX(-Cards::IMG_WIDTH_S*j);
                    j*=0.25F;
                }
            }else{
                LOG_ERROR("Hovered card not in hand, How?");
            }
        }
    }

    void Card_group_handler::hand_hide(){
        for(const auto&it:hand_cards) it->SetY(-Cards::IMG_HEIGHT);
    }

    Card_group Card_group_handler::get_upgradeable_card_group()const{
        Card_group re;
        for(const auto&it:this->master_deck)
            if(!it->IsUpgraded())re.AddTop(it);
        return re;
    }

    const std::shared_ptr<Draw::ReTexture>&Card_group_handler::reticleBlock_img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/reticleBlock.png"),&Card_group_handler::reticleArrow_img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/reticleArrow.png");
    const int &Card_group_handler::input_x=RUtil::Game_Input::getX(),&Card_group_handler::input_y=RUtil::Game_Input::getY();
    const bool &Card_group_handler::just_r=RUtil::Game_Input::just_clicked_R(),&Card_group_handler::just_l=RUtil::Game_Input::just_clicked();
    
}
