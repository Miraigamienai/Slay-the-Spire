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
    force_render_cards,
    force_update_cards
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
    void render_hand(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void obtain(const std::shared_ptr<Cards> &card);
    Card_group get_upgradeable_card_group()const;
    
    void render_force_cards(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        for(const auto&it:force_render_cards) it->render(r2);
    }
    void update_force_cards(Effect::Effect_group &top_effs)const{
        for(const auto&it:force_update_cards) it->update(top_effs);
    }
    void render_flying_cards(const std::shared_ptr<Draw::Draw_2D> &r2)const{for(const auto&it:flying_cards) it->render(r2);}
    void update_flying_cards(Effect::Effect_group &top_effs){
        for (auto it = flying_cards.begin(); it != flying_cards.end();) {
            (*it)->update(top_effs);
            if (!(*it)->is_fly())
                it = flying_cards.erase(it);
            else
                ++it;
        }
    }
    template <GroupType GT>
    void erase(const std::shared_ptr<Cards> &card){
        this->GetCards<GT>().erase(card);
    }
    template <GroupType GT>
    void AddTop(std::shared_ptr<Cards> &&card){
        this->GetCards<GT>().AddTop(std::move(card));
    }
    template <GroupType GT>
    void AddTop(const std::shared_ptr<Cards> &card){
        this->GetCards<GT>().AddTop(card);
    }
    template <GroupType GT>
    void AddBot(std::shared_ptr<Cards> &&card){
        this->GetCards<GT>().AddBot(std::move(card));
    }
    template <GroupType GT>
    void AddBot(const std::shared_ptr<Cards> &card){
        this->GetCards<GT>().AddBot(card);
    }
    template <GroupType GT>
    auto size() noexcept{
        return this->GetCards<GT>().size();
    }
    void super_flash()const{
        for(const auto&it:hand_cards) if(it->CanUse()) it->SuperFlash();
    }
    bool is_someone_canuse()const{
        for(const auto&it:hand_cards) if(it->CanUse()) return true;
        return false;
    }
    template <Card::Type CT>
    bool has_any_type_card()const{
        for(const auto&it:hand_cards) if(it->type==CT) return true;
        return false;
    }
    template <Card::Type CT>
    bool has_all_type_card()const{
        for(const auto&it:hand_cards) if(it->type!=CT) return false;
        return true;
    }
    bool can_upgrade_card()const{return this->master_deck.CanUpgradeCard();} 
    bool is_dragging() const noexcept{return is_dragging_card;}
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
    Template::Group_template<std::list<std::shared_ptr<Card::Cards>>> force_render_cards;//it will be rendered when render hand_cards, may change.
    Template::Group_template<std::list<std::shared_ptr<Card::Cards>>> force_update_cards;//it will be updated when hand_cards update.
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
    
    template <GroupType GT>
    auto& GetCards()noexcept{
        if constexpr(GT==GroupType::hand_cards) return hand_cards;
        else if constexpr(GT==GroupType::m_discard) return m_discard;
        else if constexpr(GT==GroupType::draw_pile) return draw_pile;
        else if constexpr(GT==GroupType::master_deck) return master_deck;
        else if constexpr(GT==GroupType::exhaust_pile) return exhaust_pile;
        else if constexpr(GT==GroupType::force_render_cards) return force_render_cards;
        else if constexpr(GT==GroupType::force_update_cards) return force_update_cards;
    }

    static const std::shared_ptr<Draw::ReTexture>&reticleBlock_img,&reticleArrow_img;
    static constexpr float SINK_START=80.0F*Setting::SCALE,SINK_RANGE=300.0F*Setting::SCALE,INCREMENT_ANGLE=5.0F,UI_THRESHOLD=1.0F*Setting::SCALE;
    static constexpr int ARROW_COLOR=RUtil::Math::GetColorUint32_RGB(1.0F,0.2F,0.3F);
};
}