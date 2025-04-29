#pragma once

#include <list>//flying cards
#include <memory>//shared_ptr
#include <SDL_stdinc.h>//Uint32

#include "Game_object/card/Cards.hpp"//for card inline update or render
#include "Game_object/card/Card_group.hpp"//member
#include "Game_object/effect/Effect_group.hpp"//for inline add
#include "Game_object/character/Player.hpp"//for inline glow card update

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
namespace Dungeon{
    class Dungeon_shared;
}

namespace Card{
enum class GroupType{
    hand_cards,
    m_discard,
    draw_pile,
    master_deck,
    exhaust_pile,
    force_render_cards
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
    void discard(const std::shared_ptr<Cards> &card, bool visual_only=false);
    void draw();
    void update(Action::Action_group_handler &action_group_handler,const Monster::Monster_group &room_monsters);
    void refresh_hand_layout()const;
    void prepare_for_battle(RUtil::Random &rng);
    void shuffle(bool shuffle_invisible);
    void hand_hide();
    void update_hand_cards(Effect::Effect_group &top_effs, const Dungeon::Dungeon_shared &dungeon_shared);
    void render_hand(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 PlayerColor_RGB)const;

    void render_flying_cards(const std::shared_ptr<Draw::Draw_2D> &r2, const Uint32 PlayerColor_RGB)const{for(const auto&it:flying_cards) it->render(r2,PlayerColor_RGB);}
    void update_flying_cards(Effect::Effect_group &top_effs, Uint32 PlayerTrailColor_RGB){
        for (auto it = flying_cards.begin(); it != flying_cards.end();) {
            (*it)->update(top_effs,PlayerTrailColor_RGB);
            if (!(*it)->is_fly())
                it = flying_cards.erase(it);
            else
                ++it;
        }
    }
    void erase(GroupType type, const std::shared_ptr<Cards> &card){
        switch (type) {
            case GroupType::draw_pile:
                draw_pile.erase(card);
                break;
            case GroupType::exhaust_pile:
                exhaust_pile.erase(card);
                break;
            case GroupType::hand_cards:
                hand_cards.erase(card);
                break;
            case GroupType::m_discard:
                m_discard.erase(card);
                break;
            case GroupType::master_deck:
                master_deck.erase(card);
                break;
            default:
                force_render_cards.erase(card);
                break;
        }
    }
    void AddTop(GroupType type, std::shared_ptr<Cards> &&card){
        switch (type) {
            case GroupType::draw_pile:
                draw_pile.AddTop(std::move(card));
                break;
            case GroupType::exhaust_pile:
                exhaust_pile.AddTop(std::move(card));
                break;
            case GroupType::hand_cards:
                hand_cards.AddTop(std::move(card));
                break;
            case GroupType::m_discard:
                m_discard.AddTop(std::move(card));
                break;
            case GroupType::master_deck:
                master_deck.AddTop(std::move(card));
                break;
            default:
                force_render_cards.AddTop(std::move(card));
                break;
        }
    }
    void AddTop(GroupType type, const std::shared_ptr<Cards> &card){
        switch (type) {
            case GroupType::draw_pile:
                draw_pile.AddTop(card);
                break;
            case GroupType::exhaust_pile:
                exhaust_pile.AddTop(card);
                break;
            case GroupType::hand_cards:
                hand_cards.AddTop(card);
                break;
            case GroupType::m_discard:
                m_discard.AddTop(card);
                break;
            case GroupType::master_deck:
                master_deck.AddTop(card);
                break;
            default:
                force_render_cards.AddTop(card);
                break;
        }
    }
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
            case GroupType::force_render_cards:
                return force_render_cards.size();
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
    Template::Group_template<std::list<std::shared_ptr<Card::Cards>>> force_render_cards;//rendered when cards render, may change.
    std::list<std::shared_ptr<Card::Cards>> flying_cards;//shared_ptr is needed here.
    void hand_card_push()const;
    void release_card();
    void play_card(Action::Action_group_handler &action_group_handler);
    void render_targeting(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update_targeting(Action::Action_group_handler &action_group_handler);
    void update_drop_zone_status();
    void update_hovered_card();
    void handle_dragging(Action::Action_group_handler &action_group_handler);
    void check_drag_start();
    
    static const std::shared_ptr<Draw::ReTexture>&reticleBlock_img,&reticleArrow_img;
    static constexpr float SINK_START=80.0F*Setting::SCALE,SINK_RANGE=300.0F*Setting::SCALE,INCREMENT_ANGLE=5.0F,UI_THRESHOLD=1.0F*Setting::SCALE;
    static constexpr int ARROW_COLOR=RUtil::Math::GetColorUint32_RGB(1.0F,0.2F,0.3F);
};
}