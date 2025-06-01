#include "Game_object/character/Monster/JawWorm.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    JawWorm::JawWorm(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, JawWormAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false)
        {}
    
    void JawWorm::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case Monster::JawWormAction::Chomp:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{CHOMP_DAMAGE, shared_from_this(), AttackType::NONE}, dungeon_shared.player));
                break;
            case Monster::JawWormAction::Thrash:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::HOP));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{THRASH_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));    
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), THRASH_BLOCK));
                break;
            case Monster::JawWormAction::Bellow:            
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, BELLOWS_STRENGTH, shared_from_this(), shared_from_this()));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), BELLOWS_BLOCK));
                break;
            default:
                break;
        }
    }

    void JawWorm::next_move(RUtil::Random& ai_rng, const Power::Power_group &player_powers){
        auto final_next=JawWormAction::Chomp;
        if(!first_move){
            first_move=true;
        }else{
            switch(static_cast<JawWormAction>(dist.NextIndex(ai_rng))){
                case JawWormAction::Chomp:
                    if(is_current_move(JawWormAction::Chomp))
                        final_next=static_cast<JawWormAction>(dist.NextIndexWithOut(static_cast<int>(JawWormAction::Chomp), ai_rng));
                    break;
                case JawWormAction::Thrash:
                    if(is_last_two_move(JawWormAction::Thrash))
                        final_next=static_cast<JawWormAction>(dist.NextIndexWithOut(static_cast<int>(JawWormAction::Thrash), ai_rng));
                    else
                        final_next=JawWormAction::Thrash;
                    break;
                case JawWormAction::Bellow:
                    if(is_current_move(JawWormAction::Bellow))
                        final_next=static_cast<JawWormAction>(dist.NextIndexWithOut(static_cast<int>(JawWormAction::Bellow), ai_rng));
                    else
                        final_next=JawWormAction::Bellow;
                    break;
                default:
                    break;
            }
        }
        switch(final_next){
            case JawWormAction::Chomp:
                set_move(JawWormAction::Chomp, nullptr, Intent::attack, CHOMP_DAMAGE, player_powers);
                break;
            case JawWormAction::Thrash:
                set_move(JawWormAction::Thrash, nullptr, Intent::attack_defend, THRASH_DAMAGE, player_powers);
                break;
            case JawWormAction::Bellow:
                set_move(JawWormAction::Bellow, nullptr, Intent::defend_buff, player_powers);
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &JawWorm::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Jaw Worm/Jaw-worm-pretty.png");
}

