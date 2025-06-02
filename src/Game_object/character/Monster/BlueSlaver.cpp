#include "Game_object/character/Monster/BlueSlaver.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    BlueSlaver::BlueSlaver(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, BlueSlaverAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}
 
    void BlueSlaver::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        switch(current_move()){
            case BlueSlaverAction::Stab:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{STAB_DAMAGE, shared_from_this(), AttackType::slash_horizontal}, dungeon_shared.player));
                break;
            case BlueSlaverAction::Rake:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{RAKE_DAMAGE, shared_from_this(), AttackType::slash_diagonal}, dungeon_shared.player));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, 1, shared_from_this(), dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void BlueSlaver::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=BlueSlaverAction::Stab;
        switch(static_cast<BlueSlaverAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
            case BlueSlaverAction::Stab:
                if(is_last_two_move(BlueSlaverAction::Stab))
                    final_next=BlueSlaverAction::Rake;
                break;
            case BlueSlaverAction::Rake:
                if(!is_last_two_move(BlueSlaverAction::Rake))
                    final_next=BlueSlaverAction::Rake;
                break;
            default:
                break;
        }

        switch(final_next){
            case BlueSlaverAction::Stab:
                set_move(BlueSlaverAction::Stab, nullptr, Intent::attack, STAB_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case BlueSlaverAction::Rake:
                set_move(BlueSlaverAction::Rake, nullptr, Intent::attack_debuff, RAKE_DAMAGE, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &BlueSlaver::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Slavers/Slaver-blue-pretty.png");
}

