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
//         first_move(false)
//         {}
    
//     void TheGuardian::Action(Dungeon::Dungeon_shared &dungeon_shared){
//         switch (current_move()){
//             case TheGuardianAction::ChargingUp:
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, BELLOWS_STRENGTH, shared_from_this(), shared_from_this(), true));
//                 break;
//             case TheGuardianAction::FierceBash:
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{RUSH_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));    
//                 break;
//             case TheGuardianAction::VentSteam:            
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{RUSH_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player)); 
//                 dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Vulnerable,SKULL_BASH_VULNERABLE, shared_from_this(), dungeon_shared.player , true));
//                 break;
//             case TheGuardianAction::Whirlwind: 
//                 break;
//             default:
//                 break;
//         }
//     }

//     void TheGuardian::next_move(Dungeon::Dungeon_shared &dungeon_shared){
//         auto final_next=TheGuardianAction::Bellow;
//         if(!first_move){
//             first_move=true;
//         }else{
//             switch(static_cast<TheGuardianAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
//                 case TheGuardianAction::Rush:
//                     if(is_last_two_move(TheGuardianAction::Rush))
//                         final_next=static_cast<TheGuardianAction>(dist.NextIndexWithOut(static_cast<int>(TheGuardianAction::Rush), dungeon_shared.random_package.monster_ai_rng));
//                     else
//                         final_next=TheGuardianAction::Rush;
//                     break;
//                 case TheGuardianAction::SkullBash:
//                     final_next=static_cast<TheGuardianAction>(dist.NextIndexWithOut(static_cast<int>(TheGuardianAction::Bellow), dungeon_shared.random_package.monster_ai_rng));
//                     break;
//                 default:
//                     break;
//             }
//         }
//         switch(final_next){
//             case TheGuardianAction::Bellow:
//                 set_move(TheGuardianAction::Bellow, nullptr, Intent::buff, BELLOWS_STRENGTH, dungeon_shared.player->get_powers());
//                 break;
//             case TheGuardianAction::Rush:
//                 set_move(TheGuardianAction::Rush, nullptr, Intent::attack, RUSH_DAMAGE, dungeon_shared.player->get_powers());
//                 break;
//             case TheGuardianAction::SkullBash:
//                 set_move(TheGuardianAction::SkullBash, nullptr, Intent::attack_debuff, SKULL_BASH_DAMAGE ,dungeon_shared.player->get_powers());
//                 break;
//             default:
//                 break;
//         }
//     }

//     const std::shared_ptr<Draw::ReTexture> &TheGuardian::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlin Nob/Gremlin-nob-pretty.png");
// }

