#include "Game_object/dungeon/Dungeons.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/scene/Bottom_scene.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "Game_object/map/Map_node.hpp"
#include "Game_object/map/Map_edge.hpp"
#include "Game_object/character/Player.hpp"
#include "Game_object/effect/Effect_group.hpp"
#include "Game_object/map/Map_generator.hpp"//generate map
#include "Game_object/scene/Scenes.hpp"
#include "Game_object/reward_item/Card_reward_item.hpp"
#include "Game_object/card/Card_generate.hpp"
#include "RUtil/Random.hpp"//rng

#include "Util/Logger.hpp"

namespace Dungeon{
    Dungeons::Dungeons(Dungeon_shared &dungeon_shared,unsigned long long int random_seed):dungeon_shared(dungeon_shared),random_seed(random_seed){
        scene=std::make_shared<Scene::Bottom_scene>();
        scene->next_room();
        m_map=Map::Map_generator::Get_Map(15,7,6,dungeon_shared.random_package.map_rng);
        dungeon_shared.manager.set_display_map(m_map);
        m_current_node=nullptr;
        set_next_node_oscillate_and_edge(true);
        is_fade_in=is_fade_out=false;
        fade_color_a=0.0F;
        game_over=false;
    }
    void Dungeons::update(){
        //gen update
        dungeon_shared.gen_group.update(dungeon_shared);
        //effs update
        dungeon_shared.effs.update();
        dungeon_shared.top_effs.update();
        dungeon_shared.back_effs.update();
        //room update
        if(m_current_node!=nullptr){
            m_current_node->GetRoom()->update(dungeon_shared);
            if(m_current_node->GetRoom()->get_phase()==Room::Room_phase::complete){
                //room complete
                this->on_room_complete();
                m_current_node=nullptr;
            }
        }
        if(dungeon_shared.player->IsDie()) game_over=true;
        //card update
        dungeon_shared.card_group_handler.update_hand_cards(dungeon_shared.top_effs,dungeon_shared);
        dungeon_shared.card_group_handler.update_flying_cards(dungeon_shared.top_effs);//for test
        dungeon_shared.card_group_handler.update_force_cards(dungeon_shared.top_effs);
        //overlay update
        dungeon_shared.overlay.update(dungeon_shared.card_group_handler);
        //manager update
        dungeon_shared.manager.update(dungeon_shared);
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
        if(m_current_node!=nullptr)m_current_node->GetRoom()->render(r2);
        dungeon_shared.player->render(r2);//temporary here
        scene->render_fg(r2);
        dungeon_shared.overlay.render(r2);
        dungeon_shared.card_group_handler.render_hand(r2);//flying card also render inside it.
        dungeon_shared.card_group_handler.render_force_cards(r2);
        dungeon_shared.effs.render(r2);
        dungeon_shared.manager.render(r2);
        dungeon_shared.top_effs.render(r2);
        r2->SetColor(fade_color,fade_color_a);
        r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, Setting::WINDOW_WIDTH, Setting::WINDOW_HEIGHT);
    }
    void Dungeons::set_next_node_oscillate_and_edge(const bool value)const{
        if(m_current_node==nullptr){
            for(const auto&it:m_map[0])
                if(it!=nullptr) it->SetReadyToConnect(value);
        }else{
            m_current_node->MarkAllEdge(value);
            if(m_current_node->CanMoveRight())
                m_map[m_current_node->y+1][m_current_node->x+1]->SetReadyToConnect(value);
            if(m_current_node->CanMoveMiddle())
                m_map[m_current_node->y+1][m_current_node->x]->SetReadyToConnect(value);
            if(m_current_node->CanMoveLeft())
                m_map[m_current_node->y+1][m_current_node->x-1]->SetReadyToConnect(value);
        }
    }
    bool Dungeons::check_and_set_next_node_making_circle(){
        if(m_current_node==nullptr){
            for(const auto&it:m_map[0])
                if(it!=nullptr&&it->IsMakingCircle()){
                    m_next_node=it;
                    return true;
                }
        }else{
            if(m_current_node->CanMoveRight() && m_map[m_current_node->y+1][m_current_node->x+1]->IsMakingCircle()){
                m_next_node=m_map[m_current_node->y+1][m_current_node->x+1];
                return true;
            }else if(m_current_node->CanMoveMiddle() && m_map[m_current_node->y+1][m_current_node->x]->IsMakingCircle()){
                m_next_node=m_map[m_current_node->y+1][m_current_node->x];
                return true;
            }else if(m_current_node->CanMoveLeft() && m_map[m_current_node->y+1][m_current_node->x-1]->IsMakingCircle()){
                m_next_node=m_map[m_current_node->y+1][m_current_node->x-1];
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
            fade_color_a = RUtil::Math::interpolation_fade(0.0F,1.0F,fade_timer/0.8F);
            if(fade_timer<0.0F){
                fade_timer=0.0F;
                fade_color_a=0.0F;
                is_fade_in=false;
            }
        }else if(is_fade_out){
            fade_color_a = RUtil::Math::interpolation_fade(1.0F,0.0F,fade_timer/0.8F);
            if(fade_timer<0.0F){
                fade_timer=0.0F;
                fade_color_a=1.0F;
                is_fade_out=false;
            }
        }else LOG_ERROR("Not fading but the update_fading() be called.");
    }
    void Dungeons::change_current_node_to_next(){
        if(m_next_node==nullptr){
            LOG_ERROR("Error when change current node.");
            return;
        }
        if(m_current_node!=nullptr){
            m_current_node->GetConnectedEdge(m_next_node)->MarkTaken(true);
        }
        m_current_node=m_next_node;
        m_current_node->MarkTaken();
        m_next_node=nullptr;
    }
    void Dungeons::entering_next_room(){
        set_next_node_oscillate_and_edge(false);
        change_current_node_to_next();
        set_next_node_oscillate_and_edge(true);
        fade_in();
        dungeon_shared.effs.clear();
        dungeon_shared.top_effs.clear();
        m_current_node->GetRoom()->init_room(dungeon_shared.random_package, fade_color);
        dungeon_shared.random_package.ResetRoomRNGs(this->random_seed+m_current_node->y);
        dungeon_shared.manager.hide_dungeon_screen_instantly();
        dungeon_shared.card_group_handler.prepare_for_battle(dungeon_shared.random_package.card_shuffle_rng);
        dungeon_shared.action_group_handler.prepare_for_battle();
        scene->next_room();

    }
    void Dungeons::on_room_complete(){
        if(m_current_node->GetRoom()->room_type==Room::Room_type::Monster){
            //random 3 cards
            std::vector<std::shared_ptr<Card::Cards>> card_vec;
            for(int i=0;i<3;i++) card_vec.emplace_back(Card::Card_generate::GetRandomRedCard(dungeon_shared.random_package.card_reward_rng));
            std::vector<std::shared_ptr<Reward::Reward_item>> reward_vec;
            reward_vec.emplace_back(std::make_shared<Reward::Card_reward_item>(card_vec));
            dungeon_shared.manager.open<Interface::ScreenType::combat_reward>(reward_vec);
        }
    }
}