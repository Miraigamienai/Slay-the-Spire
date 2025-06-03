#include "Game_object/character/Monster/AcidSlimeM.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    AcidSlimeM::AcidSlimeM(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, AcidSlimeMAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}

    void AcidSlimeM::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        switch (current_move()){
            case AcidSlimeMAction::CorrosiveSpit:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{CORROSIVE_SPIT_DAMAGE, shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                // TODO:shuffles 1 Slimed into the discard pile.
                break;
            case AcidSlimeMAction::Lick:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, 1, shared_from_this(), dungeon_shared.player, true));
                break;
            case AcidSlimeMAction::Tackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void AcidSlimeM::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=AcidSlimeMAction::CorrosiveSpit;
        switch(static_cast<AcidSlimeMAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
            case AcidSlimeMAction::CorrosiveSpit:
                if(is_last_two_move(AcidSlimeMAction::CorrosiveSpit))
                    final_next=static_cast<AcidSlimeMAction>(dist.NextIndexWithOut(static_cast<int>(AcidSlimeMAction::CorrosiveSpit), dungeon_shared.random_package.monster_ai_rng));
                break;
            case AcidSlimeMAction::Lick:
                if(is_last_two_move(AcidSlimeMAction::Lick))
                    final_next=static_cast<AcidSlimeMAction>(dist.NextIndexWithOut(static_cast<int>(AcidSlimeMAction::Lick), dungeon_shared.random_package.monster_ai_rng));
                else
                    final_next=AcidSlimeMAction::Lick;
                break;
            case AcidSlimeMAction::Tackle:
                if(is_current_move(AcidSlimeMAction::Tackle))
                    final_next=static_cast<AcidSlimeMAction>(dist.NextIndexWithOut(static_cast<int>(AcidSlimeMAction::Tackle), dungeon_shared.random_package.monster_ai_rng));
                else
                    final_next=AcidSlimeMAction::Tackle;
                break;
            default:
                break;
        }
            
        switch(final_next){
            case AcidSlimeMAction::CorrosiveSpit:
                set_move(AcidSlimeMAction::CorrosiveSpit, nullptr, Intent::attack_debuff, CORROSIVE_SPIT_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case AcidSlimeMAction::Lick:
                set_move(AcidSlimeMAction::Lick, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
                break;
            case AcidSlimeMAction::Tackle:
                set_move(AcidSlimeMAction::Tackle, nullptr, Intent::attack, TACKLE_DAMAGE, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &AcidSlimeM::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Acid Slime/Acid-slime-m-pretty.png");
}