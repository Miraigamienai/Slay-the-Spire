// #include "Game_object/character/Monster/TheGuardian.hpp"
// #include "Game_object/dungeon/Dungeon_shared.hpp"
// #include "Game_object/action/Damage_action.hpp"
// #include "Game_object/action/Gain_block_action.hpp"
// #include "Game_object/action/Anim_set_action.hpp"
// #include "Game_object/action/Apply_power_action.hpp"
// #include "RUtil/Image_book.hpp"
// #include "RUtil/Random.hpp"

// namespace Monster{
//     TheGuardian::TheGuardian(float offset_x, float offset_y, RUtil::Random& rng)
//         :Abstraction::Monster_move_tracker<2, TheGuardianAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
//         first_move(false),
//         in_defensive_mode(false),
//         defensive_mode_counter(0)
//         {}
    
//     void TheGuardian::Action(Dungeon::Dungeon_shared &dungeon_shared){
//         switch (current_move()){
//             case TheGuardianAction::Bellow:
//                 // 鼓風 - 增加力量
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(
//                     RUtil::Powers_Text_ID::Strength, BELLOWS_STRENGTH, shared_from_this(), shared_from_this(), true));
//                 break;
                
//             case TheGuardianAction::Rush:
//                 // 衝撞 - 造成傷害
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
//                     Damage_info{RUSH_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));    
//                 break;
                
//             case TheGuardianAction::SkullBash:
//                 // 顱擊 - 造成傷害並給予易傷
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
//                     Damage_info{SKULL_BASH_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player)); 
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(
//                     RUtil::Powers_Text_ID::Vulnerable, SKULL_BASH_VULNERABLE, shared_from_this(), dungeon_shared.player, true));
//                 break;
                
//             case TheGuardianAction::DefensiveMode:
//                 // 防禦模式 - 獲得護甲並切換姿態
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(
//                     DEFENSIVE_MODE_BLOCK, shared_from_this()));
//                 // 切換到防禦模式
//                 in_defensive_mode = true;
//                 defensive_mode_counter = 0;
//                 // 可以在這裡添加動畫切換
//                 break;
                
//             case TheGuardianAction::RollAttack:
//                 // 滾動攻擊 - 造成傷害
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
//                     Damage_info{ROLL_ATTACK_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
//                 defensive_mode_counter++;
//                 break;
                
//             case TheGuardianAction::TwinSlam:
//                 // 雙重打擊 - 造成兩次傷害
//                 for (int i = 0; i < TWIN_SLAM_TIMES; i++) {
//                     dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
//                         Damage_info{TWIN_SLAM_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
//                 }
//                 defensive_mode_counter++;
//                 break;
                
//             case TheGuardianAction::Whirlwind:
//                 // 旋風 - 造成多次傷害
//                 for (int i = 0; i < WHIRLWIND_TIMES; i++) {
//                     dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
//                         Damage_info{WHIRLWIND_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
//                 }
//                 defensive_mode_counter++;
//                 break;
                
//             case TheGuardianAction::ChargedUp:
//                 // 充能完畢 - 從防禦模式切回攻擊模式
//                 in_defensive_mode = false;
//                 // 可以在這裡添加動畫切換回攻擊姿態
//                 break;
                
//             default:
//                 break;
//         }
//     }

// void TheGuardian::next_move(Dungeon::Dungeon_shared &dungeon_shared){
//     auto final_next = TheGuardianAction::Rush; // 預設動作
    
//     if (!first_move){
//         first_move = true;
//         final_next = TheGuardianAction::Bellow; // 第一回合總是使用鼓風
//     } else {
//         // 防禦模式檢查
//         if (in_defensive_mode && defensive_mode_counter >= 3) {
//             final_next = TheGuardianAction::ChargedUp; // 達到回合數，切換回攻擊模式
//         }
//         // 攻擊模式下檢查是否需要進入防禦模式
//         else if (!in_defensive_mode && current_HP < MAX_HP * 0.5f && !is_last_two_move(TheGuardianAction::DefensiveMode)) {
//             final_next = TheGuardianAction::DefensiveMode;
//         }
//         // 正常行動選擇
//         else if (!in_defensive_mode) {
//             // 攻擊模式選擇
//             switch(static_cast<TheGuardianAction>(attack_move_dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
//                 case TheGuardianAction::Bellow:
//                     if(is_last_two_move(TheGuardianAction::Bellow))
//                         final_next = static_cast<TheGuardianAction>(attack_move_dist.NextIndexWithOut(
//                             static_cast<int>(TheGuardianAction::Bellow), dungeon_shared.random_package.monster_ai_rng));
//                     else
//                         final_next = TheGuardianAction::Bellow;
//                     break;
                    
//                 case TheGuardianAction::Rush:
//                     if(is_last_two_move(TheGuardianAction::Rush))
//                         final_next = static_cast<TheGuardianAction>(attack_move_dist.NextIndexWithOut(
//                             static_cast<int>(TheGuardianAction::Rush), dungeon_shared.random_package.monster_ai_rng));
//                     else
//                         final_next = TheGuardianAction::Rush;
//                     break;
                    
//                 case TheGuardianAction::SkullBash:
//                     if(is_last_two_move(TheGuardianAction::SkullBash))
//                         final_next = static_cast<TheGuardianAction>(attack_move_dist.NextIndexWithOut(
//                             static_cast<int>(TheGuardianAction::SkullBash), dungeon_shared.random_package.monster_ai_rng));
//                     else
//                         final_next = TheGuardianAction::SkullBash;
//                     break;
                    
//                 default:
//                     break;
//             }
//         } else {
//             // 防禦模式選擇
//             switch(static_cast<TheGuardianAction>(defensive_move_dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
//                 case TheGuardianAction::RollAttack:
//                     if(is_current_move(TheGuardianAction::RollAttack))
//                         final_next = static_cast<TheGuardianAction>(defensive_move_dist.NextIndexWithOut(
//                             static_cast<int>(TheGuardianAction::RollAttack), dungeon_shared.random_package.monster_ai_rng));
//                     else
//                         final_next = TheGuardianAction::RollAttack;
//                     break;
                    
//                 case TheGuardianAction::TwinSlam:
//                     if(is_current_move(TheGuardianAction::TwinSlam))
//                         final_next = static_cast<TheGuardianAction>(defensive_move_dist.NextIndexWithOut(
//                             static_cast<int>(TheGuardianAction::TwinSlam), dungeon_shared.random_package.monster_ai_rng));
//                     else
//                         final_next = TheGuardianAction::TwinSlam;
//                     break;
                    
//                 case TheGuardianAction::Whirlwind:
//                     if(is_current_move(TheGuardianAction::Whirlwind))
//                         final_next = static_cast<TheGuardianAction>(defensive_move_dist.NextIndexWithOut(
//                             static_cast<int>(TheGuardianAction::Whirlwind), dungeon_shared.random_package.monster_ai_rng));
//                     else
//                         final_next = TheGuardianAction::Whirlwind;
//                     break;
                    
//                 default:
//                     break;
//             }
//         }
//     }
    
//     switch(final_next){
//         case TheGuardianAction::Bellow:
//             set_move(TheGuardianAction::Bellow, nullptr, Intent::buff, BELLOWS_STRENGTH, dungeon_shared.player->get_powers());
//             break;
            
//         case TheGuardianAction::Rush:
//             set_move(TheGuardianAction::Rush, nullptr, Intent::attack, RUSH_DAMAGE, dungeon_shared.player->get_powers());
//             break;
            
//         case TheGuardianAction::SkullBash:
//             set_move(TheGuardianAction::SkullBash, nullptr, Intent::attack_debuff, SKULL_BASH_DAMAGE, dungeon_shared.player->get_powers());
//             break;
            
//         case TheGuardianAction::DefensiveMode:
//             set_move(TheGuardianAction::DefensiveMode, nullptr, Intent::defend_buff, DEFENSIVE_MODE_BLOCK, dungeon_shared.player->get_powers());
//             break;
            
//         case TheGuardianAction::RollAttack:
//             set_move(TheGuardianAction::RollAttack, nullptr, Intent::attack, ROLL_ATTACK_DAMAGE, dungeon_shared.player->get_powers());
//             break;
            
//         case TheGuardianAction::TwinSlam:
//             set_move(TheGuardianAction::TwinSlam, nullptr, Intent::attack, TWIN_SLAM_DAMAGE * TWIN_SLAM_TIMES, dungeon_shared.player->get_powers());
//             break;
            
//         case TheGuardianAction::Whirlwind:
//             set_move(TheGuardianAction::Whirlwind, nullptr, Intent::attack, WHIRLWIND_DAMAGE * WHIRLWIND_TIMES, dungeon_shared.player->get_powers());
//             break;
            
//         case TheGuardianAction::ChargedUp:
//             set_move(TheGuardianAction::ChargedUp, nullptr, Intent::unknown, 0, dungeon_shared.player->get_powers());
//             break;
            
//         default:
//             break;
//     }
// }

//     // 定義圖片資源
//     const std::shared_ptr<Draw::ReTexture> &TheGuardian::IMG = RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/The Guardian/The-guardian-atk-pretty.png");
//     const std::shared_ptr<Draw::ReTexture> &TheGuardian::DEF_IMG = RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/The Guardian/The-guardian-def-pretty.png");
// }