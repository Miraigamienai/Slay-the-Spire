#include "Game_object/character/Monster/SlimeBoss.hpp"
#include "Game_object/character/Monster/AcidSlimeL.hpp"
#include "Game_object/character/Monster/SpikeSlimeL.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "Game_object/action/Wait_action.hpp"
#include "Game_object/action/Show_card_to_discard_action.hpp"
#include "Game_object/action/Death_lock_action.hpp"
#include "Game_object/action/Suicide_action.hpp"
#include "Game_object/action/Spawn_monster_action.hpp"
#include "Game_object/effect_gen/Weighty_impact_gen.hpp"
#include "Game_object/card/status/Slimed.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    SlimeBoss::SlimeBoss(float offset_x, float offset_y)
        :Abstraction::Monster_move_tracker<0, SlimeBossAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, HP, IMG),
        move_cnt(0){}
    
    void SlimeBoss::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (move_cnt == SPLIT_CNT ? SlimeBossAction::Split : pattern[move_cnt]){
            case SlimeBossAction::GoopSpray:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_discard_action>(std::make_shared<Card::Status::Slimed>(), 3));
                break;
            case SlimeBossAction::Preparing:
                //TODO: talk
                break;
            case SlimeBossAction::Slam:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::JUMP));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Weighty_impact_gen>(dungeon_shared.player->GetcX(), dungeon_shared.player->GetcY(), 0.1F, 0.1F), 0.0F));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Wait_action>(0.8F));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::poison}, dungeon_shared.player)); 
                break;
            case SlimeBossAction::Split:  
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Death_lock_action>(shared_from_this(), true));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::SHAKE, 1.0F, 0.1F));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Suicide_action>(shared_from_this()));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Spawn_monster_action>(std::make_shared<Monster::SpikeSlimeL>(-385.0F, 20.0F, current_HP)));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Spawn_monster_action>(std::make_shared<Monster::AcidSlimeL>(120.0F, -8.0F, current_HP)));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Death_lock_action>(shared_from_this(), false));
                break;
            default:
                break;
        }
        ++move_cnt;
        if(move_cnt>=3) move_cnt=0;
    }

    void SlimeBoss::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        switch(pattern[move_cnt]){
            case SlimeBossAction::GoopSpray:
                set_move(SlimeBossAction::GoopSpray, nullptr, Intent::strong_debuff, dungeon_shared.player->get_powers());
                break;
            case SlimeBossAction::Preparing:
                set_move(SlimeBossAction::Preparing, nullptr, Intent::unknown, dungeon_shared.player->get_powers());
                break;
            case SlimeBossAction::Slam:
                set_move(SlimeBossAction::Slam, nullptr, Intent::attack, SLAM_DAMAGE, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    void SlimeBoss::damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared){
        Monsters::damage(damage_info, dungeon_shared);
        if(current_HP<=HP/2 && move_cnt!=SPLIT_CNT){
            move_cnt=SPLIT_CNT;
            set_move(SlimeBossAction::Split, nullptr, Intent::unknown, dungeon_shared.player->get_powers());
            //TODO: interrupted text
        }
    }

    const std::shared_ptr<Draw::ReTexture> &SlimeBoss::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Slime Boss/SlimeBoss.png");
}

