#include "Game_object/character/Monster/RedSlaver.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    RedSlaver::RedSlaver(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, RedSlaverAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false),
        used_entangle(false){}

    void RedSlaver::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch(current_move()){
            case RedSlaverAction::Entangle:
                //TODO: Applies 1  Entangled(You may not play any Attacks this turn.).
                break;
            case RedSlaverAction::Stab:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{STAB_DAMAGE, shared_from_this(), AttackType::slash_horizontal}, dungeon_shared.player));
                break;
            case RedSlaverAction::Scrape:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{SCRAPE_DAMAGE, shared_from_this(), AttackType::slash_diagonal}, dungeon_shared.player));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Vulnerable, 1, shared_from_this(), dungeon_shared.player, true));
                break;
            default:
                break;
        }
    }

    void RedSlaver::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=RedSlaverAction::Stab;
        if(!first_move){
            first_move=true;
        }else{
            if(!used_entangle){
                switch(static_cast<RedSlaverAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
                    case RedSlaverAction::Entangle:
                        used_entangle=true;
                        final_next=RedSlaverAction::Entangle;
                        break;
                    case RedSlaverAction::Stab:
                    case RedSlaverAction::Scrape:
                        if(!is_last_two_move(RedSlaverAction::Scrape))
                            final_next=RedSlaverAction::Scrape;
                        break;
                    default:
                        break;
                }
            }else{
                switch(static_cast<RedSlaverAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
                    case RedSlaverAction::Entangle:
                    case RedSlaverAction::Stab:
                        if(is_last_two_move(RedSlaverAction::Stab))
                            final_next=RedSlaverAction::Scrape;
                        break;
                    case RedSlaverAction::Scrape:
                        if(!is_last_two_move(RedSlaverAction::Scrape))
                            final_next=RedSlaverAction::Scrape;
                        break;
                    default:
                        break;
                }
            }
        }

        switch(final_next){
            case RedSlaverAction::Entangle:
                set_move(RedSlaverAction::Entangle, nullptr, Intent::strong_debuff, dungeon_shared.player->get_powers());
                break;
            case RedSlaverAction::Stab:
                set_move(RedSlaverAction::Stab, nullptr, Intent::attack, STAB_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case RedSlaverAction::Scrape:
                set_move(RedSlaverAction::Scrape, nullptr, Intent::attack_debuff, SCRAPE_DAMAGE, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &RedSlaver::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Slavers/Slaver-red-pretty.png");
}

