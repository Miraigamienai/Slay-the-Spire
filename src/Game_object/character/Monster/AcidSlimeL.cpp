#include "Game_object/character/Monster/AcidSlimeL.hpp"
#include "Game_object/character/Monster/AcidSlimeM.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/action/Show_card_to_discard_action.hpp"
#include "Game_object/action/Death_lock_action.hpp"
#include "Game_object/action/Suicide_action.hpp"
#include "Game_object/action/Spawn_monster_action.hpp"
#include "Game_object/card/status/Slimed.hpp"
#include "Game_object/power/Split_power.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    AcidSlimeL::AcidSlimeL(float offset_x, float offset_y, RUtil::Random& rng)
        :AcidSlimeL(offset_x, offset_y, rng.NextInt(MIN_HP, MAX_HP+1))
    {
        add_power(std::make_shared<Power::Split_power>(type));
    }
    
    AcidSlimeL::AcidSlimeL(float offset_x, float offset_y, int HP)
        :Abstraction::Monster_move_tracker<2, AcidSlimeLAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, HP, IMG),
        offset_x(offset_x),
        offset_y(offset_y),
        current_max_hp(HP){}

    void AcidSlimeL::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case AcidSlimeLAction::CorrosiveSpit:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_discard_action>(std::make_shared<Card::Status::Slimed>(), 2));
                break;
            case AcidSlimeLAction::Lick:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, 2, shared_from_this(), dungeon_shared.player, true));
                break;
            case AcidSlimeLAction::Tackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                break;
            case AcidSlimeLAction::Split:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Death_lock_action>(shared_from_this(), true));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::SHAKE, 1.0F, 0.1F));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Suicide_action>(shared_from_this()));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Spawn_monster_action>(std::make_shared<Monster::AcidSlimeM>(offset_x-134.0F, offset_y+RUtil::Random::GetRandomFloat(-4.0F, 4.0F), current_HP)));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Spawn_monster_action>(std::make_shared<Monster::AcidSlimeM>(offset_x+134.0F, offset_y+RUtil::Random::GetRandomFloat(-4.0F, 4.0F), current_HP)));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Death_lock_action>(shared_from_this(), false));
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

    void AcidSlimeL::damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared, bool deduct_block){
        Monsters::damage(damage_info, dungeon_shared, deduct_block);
        if(current_HP<=current_max_hp/2 && !is_current_move(AcidSlimeLAction::Split)){
            set_move(AcidSlimeLAction::Split, nullptr, Intent::unknown, dungeon_shared.player->get_powers());
            //TODO: interrupted text
        }
    }

    const std::shared_ptr<Draw::ReTexture> &AcidSlimeL::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Acid Slime/Acid-slime-l-pretty.png");
}

