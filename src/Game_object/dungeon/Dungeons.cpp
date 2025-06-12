#include "Game_object/dungeon/Dungeons.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/scene/Bottom_scene.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "Game_object/map/Map_node.hpp"
#include "Game_object/map/Map_edge.hpp"
#include "Game_object/character/Player.hpp"
#include "Game_object/character/Monster_group_creater.hpp"
#include "Game_object/effect/Effect_group.hpp"
#include "Game_object/map/Map_generator.hpp"//generate map
#include "Game_object/scene/Scenes.hpp"
#include "RUtil/Probability_selector.hpp"
#include "RUtil/Image_book.hpp"
#include "TheApp.hpp"

#include "Util/Logger.hpp"

namespace Dungeon{
    static constexpr auto ROOM_PROBABILITY = RUtil::make_probability_selector(
        std::array{
            std::pair{Room::Room_type::Elite, 0.08F},
            std::pair{Room::Room_type::Event, 0.22F},
            std::pair{Room::Room_type::Rest, 0.12F},
            std::pair{Room::Room_type::Shop, 0.05F},
            std::pair{Room::Room_type::Monster, 0.53F}
        }
    );
    static constexpr auto WEAK_MONSTER_PROBABILITY = RUtil::make_probability_selector(
        std::array{
            std::pair{Monster::GroupName::Cultist, 2.0F},
            std::pair{Monster::GroupName::Jaw_Worm, 2.0F},
            std::pair{Monster::GroupName::_2_Louse, 2.0F},
            std::pair{Monster::GroupName::Small_Slimes, 2.0F}
        }
    );
    static constexpr auto STRONG_MONSTER_PROBABILITY = RUtil::make_probability_selector(
        std::array{
            std::pair{Monster::GroupName::Blue_Slaver, 2.0F},
            std::pair{Monster::GroupName::Gremlin_Gang, 1.0F},
            std::pair{Monster::GroupName::Looter, 2.0F},
            std::pair{Monster::GroupName::Large_Slime, 2.0F},
            std::pair{Monster::GroupName::Lots_of_Slimes, 1.0F},
            std::pair{Monster::GroupName::Exordium_Thugs, 1.5F},
            std::pair{Monster::GroupName::Exordium_Wildlife, 1.5F},
            std::pair{Monster::GroupName::Red_Slaver, 1.0F},
            std::pair{Monster::GroupName::_3_Louse, 2.0F},
            std::pair{Monster::GroupName::_2_Fungi_Beasts, 2.0F},
        }
    );
    static constexpr auto ELITE_PROBABILITY = RUtil::make_probability_selector(
        std::array{
            std::pair{Monster::GroupName::Gremlin_Nob, 1.0F},
            std::pair{Monster::GroupName::Lagavulin, 1.0F},
            std::pair{Monster::GroupName::_3_Sentries, 1.0F}
        }
    );
    static constexpr auto BOSS_PROBABILITY = RUtil::make_probability_selector(
        std::array{
            std::pair{Monster::GroupName::The_Guardian, 1.0F},
            std::pair{Monster::GroupName::Hexaghost, 1.0F},
            std::pair{Monster::GroupName::Slime_Boss, 1.0F}
        }
    );

    static inline auto &GetBossImage(Monster::GroupName boss_name, const std::string&folder_str){
        switch(boss_name){
            case Monster::GroupName::The_Guardian:return RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/" + folder_str + "/guardian.png");
            case Monster::GroupName::Hexaghost:return RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/" + folder_str + "/hexaghost.png");
            case Monster::GroupName::Slime_Boss:return RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/" + folder_str + "/slime.png");
            default:
                LOG_ERROR("ERROR BOSS ENUM");
                return RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/" + folder_str + "/slime.png");
        }
    }

    Dungeons::Dungeons(Dungeon_shared &dungeon_shared, unsigned long long int random_seed, State&state)
        :dungeon_shared(dungeon_shared),
        state(state),
        random_seed(random_seed),
        fade_timer(0.0F),
        fade_color_a(0.0F),
        next_node_is_making_circle(false),
        is_fade_in(false),
        is_fade_out(false),
        boss_room(std::make_shared<Room::Monster_room>(BOSS_PROBABILITY(dungeon_shared.random_package.map_rng))),
        fighting_boss(false),
        boss_timer(0.0F),
        black_screen_target_a(1.0F),
        black_screen_a(black_screen_target_a)
    {
        scene=std::make_shared<Scene::Bottom_scene>();
        scene->next_room();
        m_map=Map::Map_generator::Get_Map(15,7,6,dungeon_shared.random_package.map_rng);
        Map::Map_generator::AssignRoom(m_map, ROOM_PROBABILITY, WEAK_MONSTER_PROBABILITY, STRONG_MONSTER_PROBABILITY, ELITE_PROBABILITY, dungeon_shared.random_package.map_rng);
        dungeon_shared.manager.set_display_map(m_map, GetBossImage(boss_room->m_group_name, "boss"), GetBossImage(boss_room->m_group_name, "bossOutline"));
        dungeon_shared.manager.open<Abstraction::ScreenType::main_dungeon>();
        set_next_node_oscillate_and_edge(true);
    }
    void Dungeons::update(){
        //gen update
        dungeon_shared.gen_group.update(dungeon_shared);
        //effs update
        dungeon_shared.effs.update();
        dungeon_shared.top_effs.update();
        dungeon_shared.back_effs.update();
        //panels update
        dungeon_shared.energy_panel.update(dungeon_shared);
        dungeon_shared.discard_panel.update(dungeon_shared);
        dungeon_shared.draw_panel.update(dungeon_shared);
        if(!dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::discard_pile)){
            //room update
            if(fighting_boss){
                boss_room->update(dungeon_shared);
                if(boss_room->get_phase() == Room::Room_phase::just_complete) dungeon_shared.manager.open<Abstraction::ScreenType::victory>();
            }else if(dungeon_shared.current_node!=nullptr){
                dungeon_shared.current_node->GetRoom()->update(dungeon_shared);
            }
        }
        //card update
        dungeon_shared.card_group_handler.update_hand_cards(dungeon_shared.top_effs,dungeon_shared);
        dungeon_shared.card_group_handler.update_flying_cards(dungeon_shared.top_effs);//for test
        //manager update
        dungeon_shared.manager.update(dungeon_shared);
        //black screen alpha update
        if(dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::NONE)) black_screen_target_a=0.0F;
        else black_screen_target_a=0.75F;
        update_black_screen_a();
        //if gameover
        if(dungeon_shared.manager.DeathBackToInitScreen() || dungeon_shared.manager.VictoryBackToInitScreen()){
            state=State::GameOver;
            dungeon_shared.effs.clear();
            dungeon_shared.back_effs.clear();
            dungeon_shared.top_effs.clear();
            dungeon_shared.gen_group.clear();
            dungeon_shared.action_group_handler.clear();
            dungeon_shared.card_group_handler.clear<Card::GroupType::master_deck>();
            dungeon_shared.card_group_handler.clear<Card::GroupType::force_render_cards>();
            dungeon_shared.card_group_handler.clear<Card::GroupType::force_update_cards>();
            dungeon_shared.player=nullptr;
            dungeon_shared.energy_panel.hide();
            dungeon_shared.discard_panel.hide();
            dungeon_shared.draw_panel.hide();
            dungeon_shared.manager.reset();//reset manager
            dungeon_shared.room_monsters.clear();
            return;
        }
        //check room in or room out
        if(!is_fade_in&&!is_fade_out){
            if(!next_node_is_making_circle){
                if(check_and_set_next_node_making_circle()){
                    //this function should only be triggered only when the node just starting to make a circle effect.
                    next_node_is_making_circle=true;
                    dungeon_shared.manager.set_current_on_top(false);
                    dungeon_shared.top_effs.AddTop(std::make_shared<Effect::Fade_wide>(fade_color));
                }
            }else{
                if(!check_and_set_next_node_making_circle()){
                    fade_out();
                }
            }
        }else{
            update_fading();
            if(fade_timer==0.0F){//finished fading.
                if(next_node_is_making_circle){//if fading is cause by node.
                    next_node_is_making_circle=false;
                    entering_next_room();
                }
            }
        }
    }
    void Dungeons::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        //TODO:black screen control
        scene->render_bg(r2);
        dungeon_shared.back_effs.render(r2);
        if(dungeon_shared.player != nullptr)dungeon_shared.player->render(r2);//temporary here
        dungeon_shared.room_monsters.render(r2);//temporary here
        scene->render_fg(r2);
        if(fighting_boss) boss_room->render(r2);
        else if(dungeon_shared.current_node!=nullptr)dungeon_shared.current_node->GetRoom()->render(r2);
        dungeon_shared.energy_panel.render(r2);
        if(!dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::discard_pile))
            dungeon_shared.discard_panel.render(r2);
        if(!dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::draw_pile))
            dungeon_shared.draw_panel.render(r2);
        dungeon_shared.card_group_handler.render_hand(r2);//flying card also render inside it.
        dungeon_shared.card_group_handler.render_force_cards(r2);
        dungeon_shared.effs.render(r2);
        if(fighting_boss) boss_room->render_higher(r2);
        else if(dungeon_shared.current_node!=nullptr)dungeon_shared.current_node->GetRoom()->render_higher(r2);
        render_black_screen(r2);
        dungeon_shared.manager.render(r2);
        if(dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::discard_pile))
            dungeon_shared.discard_panel.render(r2);
        if(dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::draw_pile))
            dungeon_shared.draw_panel.render(r2);
        dungeon_shared.top_effs.render(r2);
        r2->SetColor(fade_color,fade_color_a);
        r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, Setting::WINDOW_WIDTH, Setting::WINDOW_HEIGHT);
    }
    void Dungeons::set_next_node_oscillate_and_edge(const bool value)const{
        if(dungeon_shared.current_node==nullptr){
            for(const auto&it:m_map[0])
                if(it!=nullptr) it->SetReadyToConnect(value);
        }else{
            dungeon_shared.current_node->MarkAllEdge(value);
            if(dungeon_shared.current_node->HasEdge(Map::Direction::right))
                m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x+1]->SetReadyToConnect(value);
            if(dungeon_shared.current_node->HasEdge(Map::Direction::middle) && dungeon_shared.current_node->y!=static_cast<int>(m_map.size())-1)
                m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x]->SetReadyToConnect(value);
            if(dungeon_shared.current_node->HasEdge(Map::Direction::left))
                m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x-1]->SetReadyToConnect(value);
        }
    }
    bool Dungeons::check_and_set_next_node_making_circle(){
        if(dungeon_shared.current_node==nullptr){
            for(const auto&it:m_map[0])
                if(it!=nullptr&&it->IsMakingCircle()){
                    dungeon_shared.next_node=it;
                    return true;
                }
        }else if(dungeon_shared.current_node->y==14){
            if(dungeon_shared.manager.boss_click() && boss_timer==0.0F && !fighting_boss){
                boss_timer=0.75F;
            }
            
            if(boss_timer>0.0F){
                boss_timer-=RUtil::Game_Input::delta_time();
                if(boss_timer<0.0F){
                    boss_timer=0.0F;
                    fighting_boss=true;
                }
                return true;
            }
        }else{
            if(dungeon_shared.current_node->HasEdge(Map::Direction::right) && m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x+1]->IsMakingCircle()){
                dungeon_shared.next_node=m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x+1];
                return true;
            }else if(dungeon_shared.current_node->HasEdge(Map::Direction::middle) && m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x]->IsMakingCircle()){
                dungeon_shared.next_node=m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x];
                return true;
            }else if(dungeon_shared.current_node->HasEdge(Map::Direction::left) && m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x-1]->IsMakingCircle()){
                dungeon_shared.next_node=m_map[dungeon_shared.current_node->y+1][dungeon_shared.current_node->x-1];
                return true;
            }
        }
        return false;
    }
    void Dungeons::fade_in(){
        if(is_fade_out) LOG_ERROR("Dungeon fade_in() be triggered when fade_out() is not finished.");
        is_fade_in=true;
        fade_timer=0.8F;
    }
    void Dungeons::fade_out(){
        if(is_fade_in) LOG_ERROR("Dungeon fade_out() be triggered when fade_in() is not finished.");
        is_fade_out=true;
        fade_timer=0.8F;
    }
    void Dungeons::update_fading(){
        fade_timer-=RUtil::Game_Input::delta_time();
        if(is_fade_in){
            if(fade_timer<0.0F){
                fade_timer=0.0F;
                fade_color_a=0.0F;
                is_fade_in=false;
            }else{
                fade_color_a = RUtil::Math::interpolation_fade(0.0F,1.0F,fade_timer/0.8F);
            }
        }else if(is_fade_out){
            if(fade_timer<0.0F){
                fade_timer=0.0F;
                fade_color_a=1.0F;
                is_fade_out=false;
            }else{
                fade_color_a = RUtil::Math::interpolation_fade(1.0F,0.0F,fade_timer/0.8F);
            }
        }else LOG_ERROR("Not fading but the update_fading() be called.");
    }
    void Dungeons::change_current_node_to_next(){
        if(dungeon_shared.next_node==nullptr && !fighting_boss){
            LOG_ERROR("Error when change current node.");
            return;
        }
        if(fighting_boss){
            dungeon_shared.current_node->MarkAllEdge(true);
        }else if(dungeon_shared.current_node!=nullptr){
            dungeon_shared.current_node->GetConnectedEdge(dungeon_shared.next_node)->MarkTaken(true);
        }

        if(fighting_boss) dungeon_shared.current_node->MarkTaken();
        else{
            dungeon_shared.current_node=dungeon_shared.next_node;
            dungeon_shared.current_node->MarkTaken();
            dungeon_shared.next_node=nullptr;
        }
    }
    void Dungeons::entering_next_room(){
        set_next_node_oscillate_and_edge(false);
        change_current_node_to_next();
        set_next_node_oscillate_and_edge(true);
        fade_in();
        dungeon_shared.effs.clear();
        dungeon_shared.top_effs.clear();
        dungeon_shared.random_package.ResetRoomRNGs(this->random_seed+dungeon_shared.current_node->y);
        dungeon_shared.manager.hide_dungeon_screen_instantly();
        dungeon_shared.card_group_handler.prepare_for_battle(dungeon_shared.random_package.card_shuffle_rng);
        dungeon_shared.action_group_handler.prepare_for_battle();
        if(fighting_boss) boss_room->init_room(dungeon_shared, fade_color);
        else dungeon_shared.current_node->GetRoom()->init_room(dungeon_shared, fade_color);
        scene->next_room();
    }

    void Dungeons::render_black_screen(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::BLACK, black_screen_a);
        r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT));
    }

    void Dungeons::update_black_screen_a(){
        if(black_screen_target_a != black_screen_a){
            if(this->black_screen_target_a > this->black_screen_a){
                black_screen_a+=2.0F*RUtil::Game_Input::delta_time();
                if(black_screen_a>black_screen_target_a) black_screen_a=black_screen_target_a;
            }else{
                black_screen_a-=2.0F*RUtil::Game_Input::delta_time();
                if(black_screen_a<black_screen_target_a) black_screen_a=black_screen_target_a;
            }
        }
    }
}