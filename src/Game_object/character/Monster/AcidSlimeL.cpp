#include "Game_object/character/Monster/AcidSlimeL.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    AcidSlimeL::AcidSlimeL(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, AcidSlimeLAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}

    void AcidSlimeL::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case AcidSlimeLAction::CorrosiveSpit:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{CORROSIVE_SPIT_DAMAGE, shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                //TODO: shuffles 2 Slimed into the discard pile.
                break;
            case AcidSlimeLAction::Lick:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, 2, shared_from_this(), dungeon_shared.player, true));
                break;
            case AcidSlimeLAction::Tackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                break;
            case AcidSlimeLAction::Split:
                //TODO: spawn 2 Acid Slime M.
                break;
            default:
                break;
        }
    }

    void AcidSlimeL::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=AcidSlimeLAction::CorrosiveSpit;
        switch(static_cast<AcidSlimeLAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
            case AcidSlimeLAction::CorrosiveSpit:
                if(is_last_two_move(AcidSlimeLAction::CorrosiveSpit))
                    final_next=static_cast<AcidSlimeLAction>(dist.NextIndexWithOut(static_cast<int>(AcidSlimeLAction::CorrosiveSpit), dungeon_shared.random_package.monster_ai_rng));
                break;
            case AcidSlimeLAction::Lick:
                if(is_last_two_move(AcidSlimeLAction::Lick))
                    final_next=static_cast<AcidSlimeLAction>(dist.NextIndexWithOut(static_cast<int>(AcidSlimeLAction::Lick), dungeon_shared.random_package.monster_ai_rng));
                else
                    final_next=AcidSlimeLAction::Lick;
                break;
            case AcidSlimeLAction::Tackle:
                if(is_current_move(AcidSlimeLAction::Tackle))
                    final_next=static_cast<AcidSlimeLAction>(dist.NextIndexWithOut(static_cast<int>(AcidSlimeLAction::Tackle), dungeon_shared.random_package.monster_ai_rng));
                else
                    final_next=AcidSlimeLAction::Tackle;
                break;
            default:
                break;
        }
            
        switch(final_next){
            case AcidSlimeLAction::CorrosiveSpit:
                set_move(AcidSlimeLAction::CorrosiveSpit, nullptr, Intent::attack_debuff, CORROSIVE_SPIT_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case AcidSlimeLAction::Lick:
                set_move(AcidSlimeLAction::Lick, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
                break;
            case AcidSlimeLAction::Tackle:
                set_move(AcidSlimeLAction::Tackle, nullptr, Intent::attack, TACKLE_DAMAGE, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &AcidSlimeL::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Acid Slime/Acid-slime-l-pretty.png");
}

