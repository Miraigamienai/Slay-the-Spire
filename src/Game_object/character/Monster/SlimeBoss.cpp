#include "Game_object/character/Monster/SlimeBoss.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    SlimeBoss::SlimeBoss(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, SlimeBossAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false)
        {}
    
    void SlimeBoss::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case SlimeBossAction::GoopSpray:
                //	Shuffles 3 Slimed to your discard pile.
                break;
            case SlimeBossAction::Preparing:
                break;
            case SlimeBossAction::Slam:            
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{SLAM_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player)); 
                break;
            case SlimeBossAction::Split:  
                //Splits into an Acid Slime (L) and a Spike Slime (L) with current HP.
                break;
            default:
                break;
        }
    }

    void SlimeBoss::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=SlimeBossAction::GoopSpray;
        if(!first_move){
            first_move=true;
        }else if(current_HP<MAX_HP*0.5){
            final_next=SlimeBossAction::Split;
        }else{
            switch(static_cast<SlimeBossAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
                case SlimeBossAction::GoopSpray:
                    final_next=SlimeBossAction::Preparing;
                    break;
                case SlimeBossAction::Preparing:
                    final_next=SlimeBossAction::Slam;
                    break;
                case SlimeBossAction::Slam:
                    final_next=SlimeBossAction::GoopSpray;
                    break;
                default:
                    break;
            }
        }
        switch(final_next){
            case SlimeBossAction::GoopSpray:
                //
                set_move(SlimeBossAction::GoopSpray, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
                break;
            case SlimeBossAction::Preparing:
                set_move(SlimeBossAction::Preparing, nullptr, Intent::unknown, dungeon_shared.player->get_powers());
                break;
            case SlimeBossAction::Slam:
                set_move(SlimeBossAction::Slam, nullptr, Intent::attack, SLAM_DAMAGE ,dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &SlimeBoss::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Slime Boss/SlimeBoss.png");
}

