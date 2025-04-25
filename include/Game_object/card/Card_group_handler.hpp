#pragma once

#include <list>//flying cards
#include <memory>//shared_ptr
#include <SDL_stdinc.h>//Uint32

#include "Game_object/card/Cards.hpp"//for card inline update or render
#include "Game_object/card/Card_group.hpp"//member
#include "Game_object/effect/Effect_group.hpp"//for inline add

//fwd decl
namespace Monster{
    class Monsters;
    class Monster_group;
}
namespace Action{
    class Action_group_handler;
}
namespace RUtil{
    class Random;
}
namespace Draw{
    class Draw_2D;
    class ReTexture;
}

namespace Card{
enum class GroupType{
    hand_cards,
    m_discard,
    draw_pile,
    master_deck,
    exhaust_pile
};
class Card_group_handler
{
public:
    Card_group_handler();
    ~Card_group_handler()=default;
    Card_group_handler(const Card_group_handler &) = delete;
    Card_group_handler(Card_group_handler &&) = delete;
    Card_group_handler &operator=(const Card_group_handler &) = delete;
    Card_group_handler &operator=(Card_group_handler &&)=delete;

    void discard_all();
    void discard(const std::shared_ptr<Cards> &card);
    void draw();
    void update(Action::Action_group_handler &action_group_handler,const Monster::Monster_group &room_monsters);
    void refresh_hand_layout()const;
    void prepare_for_battle(RUtil::Random &rng);
    void shuffle(bool shuffle_invisible);
    void hand_hide();
    void render_hand(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 PlayerColor_RGB)const;
    void render_flying_cards(const std::shared_ptr<Draw::Draw_2D> &r2, const Uint32 PlayerColor_RGB)const{for(const auto&it:flying_cards) it->render(r2,PlayerColor_RGB);}
    void update_flying_cards(Effect::Effect_group &effs, Uint32 PlayerTrailColor_RGB){
        for (auto it = flying_cards.begin(); it != flying_cards.end();) {
            (*it)->update(effs,PlayerTrailColor_RGB);
            if (!(*it)->is_fly())
                it = flying_cards.erase(it);
            else
                ++it;
        }
    }
    void update_hand_cards(Effect::Effect_group &effs, Uint32 PlayerTrailColor_RGB){hand_cards.update(effs,PlayerTrailColor_RGB);}
    void add_to_master_deck(std::shared_ptr<Cards> &&card){master_deck.AddTop(std::move(card));}
    
    void super_flash()const{
        for(const auto&it:hand_cards) if(it->CanUse()) it->SuperFlash();
    }
    bool is_someone_canuse()const{
        for(const auto&it:hand_cards) if(it->CanUse()) return true;
        return false;
    }
    bool is_dragging() const noexcept{return is_dragging_card;}
    int size(GroupType type) const noexcept(
        noexcept(draw_pile.size()) &&
        noexcept(exhaust_pile.size()) &&
        noexcept(hand_cards.size()) &&
        noexcept(m_discard.size()) &&
        noexcept(master_deck.size())
    ){
        switch (type) {
            case GroupType::draw_pile:
                return draw_pile.size();
            case GroupType::exhaust_pile:
                return exhaust_pile.size();
            case GroupType::hand_cards:
                return hand_cards.size();
            case GroupType::m_discard:
                return m_discard.size();
            case GroupType::master_deck:
                return master_deck.size();
            default:
                return 0;
        }
    }
    bool is_someone_flying()const noexcept{return !flying_cards.empty();}
    void discard_pile_shuffle_with_rng(RUtil::Random &rng){m_discard.ShuffleWithRng(rng);}
private:
    static const int &input_x,&input_y;
    static const bool &just_r,&just_l;
    bool single_target,in_drop_zone,pass_hesitation_line,is_dragging_card;
    float arrowX,arrowY,hover_start_line,m_arrow_timer,arrow_scale;
    std::shared_ptr<Card::Cards> hovered_card=nullptr;
    std::shared_ptr<Monster::Monsters> hovered_monster=nullptr;
    Card_group hand_cards,m_discard,draw_pile,master_deck,exhaust_pile;
    std::list<std::shared_ptr<Card::Cards>> flying_cards;//shared_ptr is needed here.
    void hand_card_push()const;
    void release_card();
    void play_card(Action::Action_group_handler &action_group_handler);
    void render_targeting(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update_targeting();
    void update_drop_zone_status();
    void update_hovered_card();
    void handle_dragging(Action::Action_group_handler &action_group_handler);
    void check_drag_start();
    
    static const std::shared_ptr<Draw::ReTexture>&reticleBlock_img,&reticleArrow_img;
    static constexpr float SINK_START=80.0F*Setting::SCALE,SINK_RANGE=300.0F*Setting::SCALE,INCREMENT_ANGLE=5.0F,UI_THRESHOLD=1.0F*Setting::SCALE;
    static constexpr int ARROW_COLOR=RUtil::Math::GetColorUint32_RGB(1.0F,0.2F,0.3F);
};
}