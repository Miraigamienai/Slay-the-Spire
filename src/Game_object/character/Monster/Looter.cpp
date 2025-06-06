#include "Game_object/character/Monster/Looter.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    Looter::Looter(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<1, LooterAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        move_cnt(0){}

    void Looter::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch(current_move()){
            case LooterAction::Mug:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{current_damage(), shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));

                //TODO: steal 15 Gold from player.
                break;
            case LooterAction::Lunge:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{current_damage(), shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player
                ));

                //TODO: steal 15 Gold from player.
                break;
            case LooterAction::SmokeBomb:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), SMOKE_BOMB_BLOCK));
                break;
            case LooterAction::Escape:
                //TODO: escape
                break;
            default:
                break;
        }
    }

    void Looter::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        if(is_current_move(LooterAction::SmokeBomb)){
            set_move(LooterAction::Escape, nullptr, Intent::escape, dungeon_shared.player->get_powers());
            return;
        }

        if(move_cnt<2){
            set_move(LooterAction::Mug, nullptr, Intent::attack, MUG_DAMAGE, dungeon_shared.player->get_powers());
        }else if(move_cnt>2 ||(move_cnt==2&&dungeon_shared.random_package.monster_ai_rng.GetRandomBoolean())){
            set_move(LooterAction::SmokeBomb, nullptr, Intent::defend, dungeon_shared.player->get_powers());
        }else{
            set_move(LooterAction::Lunge, nullptr, Intent::attack, LUNGE_DAMAGE, dungeon_shared.player->get_powers());
        }

        ++move_cnt;
    }

    const std::shared_ptr<Draw::ReTexture> &Looter::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Thieves/Looter-pretty.png");
}

