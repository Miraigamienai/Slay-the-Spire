#include "Game_object/character/Monster/GremlinNob.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    GremlinNob::GremlinNob(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, GremlinNobAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false){}
    
    void GremlinNob::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case GremlinNobAction::Rush:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));    
                break;
            case GremlinNobAction::SkullBash:            
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player)); 
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Vulnerable, SKULL_BASH_VULNERABLE, shared_from_this(), dungeon_shared.player , true));
                break;
            case GremlinNobAction::Bellow:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Anger, BELLOWS_NUMS, shared_from_this(), shared_from_this(), true));
                break;
            default:
                break;
        }
    }

    void GremlinNob::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=GremlinNobAction::Rush;
        if(!first_move){
            final_next=GremlinNobAction::Bellow;
            first_move=true;
        }else{
            switch(static_cast<GremlinNobAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
                case GremlinNobAction::Rush:
                    if(is_last_two_move(GremlinNobAction::Rush))
                        final_next=GremlinNobAction::SkullBash;
                    break;
                case GremlinNobAction::SkullBash:
                    final_next=GremlinNobAction::SkullBash;
                    break;
                default:
                    break;
            }
        }
        switch(final_next){
            case GremlinNobAction::Bellow:
                set_move(GremlinNobAction::Bellow, nullptr, Intent::buff, dungeon_shared.player->get_powers());
                break;
            case GremlinNobAction::Rush:
                set_move(GremlinNobAction::Rush, nullptr, Intent::attack, RUSH_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case GremlinNobAction::SkullBash:
                set_move(GremlinNobAction::SkullBash, nullptr, Intent::attack_debuff, SKULL_BASH_DAMAGE ,dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &GremlinNob::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlin Nob/Gremlin-nob-pretty.png");
}

