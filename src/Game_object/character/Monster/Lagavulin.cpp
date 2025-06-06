#include "Game_object/character/Monster/Lagavulin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    Lagavulin::Lagavulin(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, LagavulinAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false)
        {}
    
    void Lagavulin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case LagavulinAction::Attack:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{ATTACK_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));    
                break;
            case LagavulinAction::SiphonSoul:
                //Inflicts -1  Dexterity,
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, SIPHONSOUL_STRENGTH, shared_from_this(), dungeon_shared.player, true));
            default:
                break;
        }
    }

    void Lagavulin::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        if(!is_awake){
            set_move(LagavulinAction::METALLICIZE, nullptr, Intent::defend, METALLICIZE_BLOCK, dungeon_shared.player->get_powers());
            return;
        }
        auto final_next=LagavulinAction::Attack;
        if(!first_move){
            first_move=true;
        }else{
            switch(static_cast<LagavulinAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
                case LagavulinAction::Attack:
                    if(is_last_two_move(LagavulinAction::Attack))
                        final_next=static_cast<LagavulinAction>(dist.NextIndexWithOut(static_cast<int>(LagavulinAction::Attack), dungeon_shared.random_package.monster_ai_rng));
                    else
                        final_next=LagavulinAction::Attack;
                    break;
                case LagavulinAction::SiphonSoul:
                    final_next=static_cast<LagavulinAction>(dist.NextIndexWithOut(static_cast<int>(LagavulinAction::SiphonSoul), dungeon_shared.random_package.monster_ai_rng));
                    break;
                default:
                    break;
            }
        }
        switch(final_next){
            case LagavulinAction::Attack:
                set_move(LagavulinAction::Attack, nullptr, Intent::attack, ATTACK_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case LagavulinAction::SiphonSoul:
                set_move(LagavulinAction::SiphonSoul, nullptr, Intent::attack_debuff,dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &Lagavulin::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Lagavulin/Lagavulin-awake-pretty.png");
}

//         break;