#include "Game_object/character/Monster/TheGuardian.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/action/Effect_capsule_action.hpp"
#include "Game_object/action/Call_action.hpp"
#include "Game_object/action/Remove_power_action.hpp"
#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "Game_object/effect_gen/Intense_zoom_gen.hpp"
#include "Game_object/effect/Cleave_eff.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    TheGuardian::TheGuardian()
        :Abstraction::Monster_move_tracker<0, TheGuardianAction>(-50.0F, 10.0F, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, HP, ATK_IMG),
        in_defensive_mode(false),
        move_cnt(1),
        damage_threshold(DAMAGE_THRESHOLD_START),
        damage_taken(0){}
    
    void TheGuardian::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch(in_defensive_mode ? DEF_PATTERN[move_cnt] : ATK_PATTERN[move_cnt]){
            case TheGuardianAction::ChargingUp:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), CHARGING_UP_BLOCK));
                //TODO: talk
                break;
            case TheGuardianAction::FierceBash:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                break;
            case TheGuardianAction::VentSteam:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, VENT_DEBUFF_CNT, shared_from_this(), dungeon_shared.player, true));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Vulnerable, VENT_DEBUFF_CNT, shared_from_this(), dungeon_shared.player, true));
                break;
            case TheGuardianAction::Whirlwind:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                for(int i=0;i<WHIRLWIND_HITS;++i){
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_capsule_action>(std::make_shared<Effect::Cleave_eff>(dungeon_shared.player->GetcX(), dungeon_shared.player->GetcY()), 0.15F, Action::Effect_capsule_action::Layer::normal));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::NONE}, dungeon_shared.player));
                }
                break;
            case TheGuardianAction::DefensiveMode:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Sharp_Hide, DEFENSIVE_MODE_SHARP, shared_from_this(), shared_from_this(), true));
                break;
            case TheGuardianAction::RollAttack:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                break;
            case TheGuardianAction::TwinSlam:
                {
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<TheGuardian, CallType, decltype(dungeon_shared)>>(std::static_pointer_cast<TheGuardian>(shared_from_this()), CallType::Offensive, dungeon_shared));
                    for(int i=0;i<2;++i)
                        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::slash_heavy}, dungeon_shared.player));
                    std::shared_ptr<Power::Powers> temp = nullptr; 
                    for(const auto&it:get_powers())
                        if(it->power_id == RUtil::Powers_Text_ID::Sharp_Hide) temp = it;
                    if(temp!=nullptr)
                        dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Remove_power_action>(temp, shared_from_this()));
                }
                break;
            default:
                break;
        }
        ++move_cnt;
        if(move_cnt >= static_cast<int>(in_defensive_mode ? DEF_PATTERN.size() : ATK_PATTERN.size()))
            move_cnt = 0;
    }
    
    void TheGuardian::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        switch(in_defensive_mode ? DEF_PATTERN[move_cnt] : ATK_PATTERN[move_cnt]){
            case TheGuardianAction::ChargingUp:
                set_move(TheGuardianAction::ChargingUp, nullptr, Intent::defend, dungeon_shared.player->get_powers());
                break;
            case TheGuardianAction::FierceBash:
                set_move(TheGuardianAction::FierceBash, nullptr, Intent::attack, FIERCE_BASH_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case TheGuardianAction::VentSteam:
                set_move(TheGuardianAction::VentSteam, nullptr, Intent::strong_debuff, dungeon_shared.player->get_powers());
                break;
            case TheGuardianAction::Whirlwind:
                set_move(TheGuardianAction::Whirlwind, nullptr, Intent::attack, WHIRLWIND_DAMAGE, WHIRLWIND_HITS, dungeon_shared.player->get_powers());
                break;
            case TheGuardianAction::DefensiveMode:
                set_move(TheGuardianAction::DefensiveMode, nullptr, Intent::buff, dungeon_shared.player->get_powers());
                break;
            case TheGuardianAction::RollAttack:
                set_move(TheGuardianAction::RollAttack, nullptr, Intent::attack, ROLL_ATTACK_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case TheGuardianAction::TwinSlam:
                set_move(TheGuardianAction::TwinSlam, nullptr, Intent::attack_buff, TWIN_SLAM_DAMAGE, 2, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }
    
    void TheGuardian::Call(CallType call_type, Dungeon::Dungeon_shared &dungeon_shared){
        switch(call_type){
            case CallType::Defensive:
                {
                    set_img(DEF_IMG);
                    damage_threshold += DAMAGE_THRESHOLD_ADD;
                    std::shared_ptr<Power::Powers> temp = nullptr; 
                    for(const auto&it:get_powers()) if(it->power_id == RUtil::Powers_Text_ID::Mode_Shift) temp = it;
                    if(temp!=nullptr) dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Remove_power_action>(temp, shared_from_this()));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), 20));
                    set_move(TheGuardianAction::DefensiveMode, nullptr, Intent::buff, dungeon_shared.player->get_powers());
                    move_cnt=0;
                }
                break;
            case CallType::Offensive:
                set_img(ATK_IMG);
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Mode_Shift, damage_threshold, shared_from_this(), shared_from_this(), true));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<TheGuardian, CallType, decltype(dungeon_shared)>>(std::static_pointer_cast<TheGuardian>(shared_from_this()), CallType::Reset, dungeon_shared));
                move_cnt=0;
                break;
            case CallType::Reset:
                damage_taken=0;
                in_defensive_mode=false;
                break;
        }
    }

    void TheGuardian::damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared, bool deduct_block){
        const int past_HP=GetCurrentHP();
        Monsters::damage(damage_info, dungeon_shared, deduct_block);
        int diff_HP= past_HP - GetCurrentHP();
        if(!in_defensive_mode && GetCurrentHP()>0 && diff_HP>0){
            damage_taken+=diff_HP;
            std::shared_ptr<Power::Powers> temp = nullptr; 
            for(const auto&it:get_powers()) if(it->power_id == RUtil::Powers_Text_ID::Mode_Shift) temp = it;
            if(temp!=nullptr) temp->reduce_amount((diff_HP>temp->get_amount() ? temp->get_amount() : diff_HP));
            if(damage_taken > damage_threshold){
                damage_taken=0;
                in_defensive_mode=true;
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Intense_zoom_gen>(GetcX(), GetcY()), 0.05F));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<TheGuardian, CallType, decltype(dungeon_shared)>>(std::static_pointer_cast<TheGuardian>(shared_from_this()), CallType::Defensive, dungeon_shared));
            }
        }
    }

    void TheGuardian::at_combat_start(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Mode_Shift, damage_threshold, shared_from_this(), shared_from_this(), true));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<TheGuardian, CallType, decltype(dungeon_shared)>>(std::static_pointer_cast<TheGuardian>(shared_from_this()), CallType::Reset, dungeon_shared));        
    }

    const std::shared_ptr<Draw::ReTexture> &TheGuardian::ATK_IMG = RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/The Guardian/The-guardian-atk-pretty.png");
    const std::shared_ptr<Draw::ReTexture> &TheGuardian::DEF_IMG = RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/The Guardian/The-guardian-def-pretty.png");
}