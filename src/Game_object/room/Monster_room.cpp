#include "Game_object/room/Monster_room.hpp"//the hpp
#include "Game_object/card/Card_group_handler.hpp"//for update
#include "Game_object/card/Card_generate.hpp"
#include "Game_object/reward_item/Card_reward_item.hpp"
#include "Game_object/reward_item/Gold_reward_item.hpp"
#include "Game_object/action/Action_group_handler.hpp"//for update
#include "Game_object/action/Draw_card_action.hpp"//draw card
#include "Game_object/action/Discard_all_action.hpp"//end turn discard
#include "Game_object/action/Enable_end_button_action.hpp"//controls the time for enabling the end button 
#include "Game_object/action/Gain_energy_action.hpp"//gain energy 
#include "Game_object/action/Effect_capsule_action.hpp"//capsule the Enemy_turn_eff
#include "Game_object/effect/Enemy_turn_eff.hpp"//apply when enemy turn start
#include "Game_object/effect/Player_turn_eff.hpp"//apply when player turn start
#include "Game_object/dungeon/Dungeon_shared.hpp"//for update function
#include "Game_object/action/Damage_action.hpp"//for damage
#include "Game_object/character/Monster_group_creater.hpp"//create monsters & group_name
#include "Game_object/character/Monster/Monsters.hpp"//render tip
#include "RUtil/Image_book.hpp"//for Retexture loading
#include "RUtil/Game_Input.hpp"//delta time
#include "Draw/ReTexture.hpp"//IMG Retexture
#include "Draw/Draw_2D.hpp"//for rendering
#include "Cursor.hpp"

#include "Util/Logger.hpp"//LOG_ERROR

//debug
#include "Util/Input.hpp"
#include "Game_object/action/Apply_power_action.hpp"

namespace Room{
Monster_room::Monster_room(Monster::GroupName group_name)
    :Monster_room(group_name, Room_type::Monster){}

Monster_room::Monster_room(Monster::GroupName group_name, Room_type type)
    :Rooms(type),
    m_group_name(group_name),
    m_wait_timer(0.0F),
    ending_battle(false),
    ending_battle_timer(0.25F),
    dungeon_fade_color(RUtil::BLACK),
    tip_character(nullptr),
    turn_count(0){}

void Monster_room::init_room(Dungeon::Dungeon_shared& dungeon_shared, Uint32 dungeon_fade_color){
    Monster::Monster_group_creater::CreateGroup(dungeon_shared, m_group_name);
    this->dungeon_fade_color=dungeon_fade_color;
    for(const auto&it:dungeon_shared.room_monsters) it->at_combat_start(dungeon_shared);
    m_wait_timer=0.1F;
}
void Monster_room::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
    end_turn_button.render(r2);
}
void Monster_room::render_higher(const std::shared_ptr<Draw::Draw_2D> &r2)const{
    if(tip_character!=nullptr) tip_character->render_tip(r2);
}
void Monster_room::update(Dungeon::Dungeon_shared &dungeon_shared){
    dungeon_shared.room_monsters.update();
    dungeon_shared.player->update();
    end_turn_button.update(dungeon_shared.card_group_handler);

    if(dungeon_shared.player->IsDie()){
        tip_character=nullptr;
        return;
    }

    if(ending_battle){
        if(ending_battle_timer>0.0F){
            ending_battle_timer-=RUtil::Game_Input::delta_time();
        }else if(this->room_phase==Room_phase::incomplete){
            this->room_phase=Room_phase::just_complete;
            to_get_reward(dungeon_shared);
        }else{
            this->room_phase=Room_phase::complete;
        }
        return;
    }

    if(!dungeon_shared.card_group_handler.is_dragging()){
        if(dungeon_shared.player->TipHovered()) tip_character=dungeon_shared.player;
        else tip_character=dungeon_shared.room_monsters.GetTipHoveredMonster();
    }else{
        tip_character=nullptr;
    }

    if(m_wait_timer<=0.0F){//Loop until end turn. //Idle also loop here.
        dungeon_shared.action_group_handler.update(dungeon_shared);
        dungeon_shared.card_group_handler.update(dungeon_shared);
        
        //debug key check
        if(Util::Input::IsKeyUp(Util::Keycode::SPACE)){
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, 99, dungeon_shared.player, dungeon_shared.player));
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Dexterity, 99, dungeon_shared.player, dungeon_shared.player));
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_energy_action>(dungeon_shared.player->GetMaxEnergy()));
            dungeon_shared.player->heal(100, dungeon_shared);
        }
        if(Util::Input::IsKeyUp(Util::Keycode::END)){
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{999, dungeon_shared.player, AttackType::NONE}, dungeon_shared.player, false));
        }

        if(dungeon_shared.discard_panel.is_logically_clicked() && !dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::discard_pile)){
            dungeon_shared.discard_panel.SetClickTimer();
            dungeon_shared.manager.open<Abstraction::ScreenType::discard_pile>(dungeon_shared);
        }
        if(dungeon_shared.draw_panel.is_logically_clicked() && !dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::draw_pile)){
            dungeon_shared.draw_panel.SetClickTimer();
            dungeon_shared.manager.open<Abstraction::ScreenType::draw_pile>(dungeon_shared);
        }

        if(end_turn_button.is_logically_clicked() && dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::NONE)){
            //ending turn
            //TODO:end logic need to be check.
            end_turn_button.disable();
            dungeon_shared.card_group_handler.on_end_of_turn(dungeon_shared);
            dungeon_shared.player->at_turn_end(dungeon_shared);
            for(const auto&it:dungeon_shared.room_monsters) it->at_turn_end(dungeon_shared);
        }else if(end_turn_button.is_disable() && dungeon_shared.action_group_handler.is_nothing_to_do()){
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Discard_all_action>());
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_capsule_action>(std::make_shared<Effect::Enemy_turn_eff>(dungeon_fade_color), 1.2F, Action::Effect_capsule_action::Layer::top));
            dungeon_shared.action_group_handler.ending_turn(dungeon_shared.room_monsters);
            dungeon_shared.room_monsters.at_turn_start(dungeon_shared);
            this->m_wait_timer=0.25F;
        }
    }else{
        if(dungeon_shared.action_group_handler.is_nothing_to_do()){
            m_wait_timer-=RUtil::Game_Input::delta_time();
        }else{
            dungeon_shared.action_group_handler.update(dungeon_shared);
        }
        if(m_wait_timer<=0.0F){//ready to start turn
            //update move
            dungeon_shared.room_monsters.next_move(dungeon_shared);
            //update turn cnt
            ++turn_count;
            if(turn_count==1){//at start of battle
                dungeon_shared.energy_panel.show();
                dungeon_shared.discard_panel.show();
                dungeon_shared.draw_panel.show();
                end_turn_button.show();
                //show hp
                dungeon_shared.room_monsters.ShowHP();
                dungeon_shared.player->ShowHP();
            }else{
                //show intent
                dungeon_shared.top_effs.AddTop(std::make_shared<Effect::Player_turn_eff>(dungeon_fade_color, turn_count));
            }
            //gain energy
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_energy_action>(dungeon_shared.player->GetMaxEnergy()));
            //temporary 5
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Draw_card_action>(5));
            
            //Ensure that enable action will be triggered after the card are drawn.
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Enable_end_button_action>(end_turn_button));
            
        }
    }

    //check does battle end
    if(dungeon_shared.room_monsters.IsAllDie() && dungeon_shared.action_group_handler.is_nothing_to_do()){
        ending_battle=true;
        tip_character=nullptr;
        dungeon_shared.player->clear_power();
        dungeon_shared.energy_panel.hide();
        dungeon_shared.discard_panel.hide();
        dungeon_shared.draw_panel.hide();
        end_turn_button.hide();
        // card_group_handler.on_ending_battle();
        Cursor::SetVisible(true);
    }
}

void Monster_room::to_get_reward(Dungeon::Dungeon_shared &dungeon_shared)const{
    std::vector<std::shared_ptr<Reward::Reward_item>> reward_vec;
    //random golds
    reward_vec.emplace_back(std::make_shared<Reward::Gold_reward_item>(dungeon_shared.random_package.reward_rng.NextInt(10, 21)));
    //random 3 cards
    std::vector<std::shared_ptr<Card::Cards>> cards;
    for(int i=0;i<3;i++) cards.emplace_back(Card::Card_generate::GetRandomRedCard(dungeon_shared.random_package.reward_rng));
    reward_vec.emplace_back(std::make_shared<Reward::Card_reward_item>(cards));
    dungeon_shared.manager.open<Abstraction::ScreenType::combat_reward>(reward_vec);
}

const std::shared_ptr<Draw::ReTexture> &Monster_room::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monster.png"),
                                       &Monster_room::IMG_O=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/map/monsterOutline.png");
}