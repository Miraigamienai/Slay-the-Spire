#include "Game_object/character/Monster/SpikeSlimeL.hpp"
#include "Game_object/character/Monster/SpikeSlimeM.hpp"
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
    SpikeSlimeL::SpikeSlimeL(float offset_x, float offset_y, RUtil::Random& rng)
        :SpikeSlimeL(offset_x, offset_y, rng.NextInt(MIN_HP, MAX_HP+1)){}
    
    SpikeSlimeL::SpikeSlimeL(float offset_x, float offset_y, int HP)
        :Abstraction::Monster_move_tracker<2, SpikeSlimeLAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, HP, IMG),
        offset_x(offset_x),
        offset_y(offset_y),
        current_max_hp(HP)
    {
        add_power(std::make_shared<Power::Split_power>(type));
    }
    
    void SpikeSlimeL::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case SpikeSlimeLAction::FlameTackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_discard_action>(std::make_shared<Card::Status::Slimed>(), 2));
                break;
            case SpikeSlimeLAction::Lick:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Frail, 2, shared_from_this(), dungeon_shared.player, true));
                break;
            case SpikeSlimeLAction::Split:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Death_lock_action>(shared_from_this(), true));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::SHAKE, 1.0F, 0.1F));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Suicide_action>(shared_from_this()));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Spawn_monster_action>(std::make_shared<Monster::SpikeSlimeM>(offset_x-134.0F, offset_y+RUtil::Random::GetRandomFloat(-4.0F, 4.0F), current_HP)));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Spawn_monster_action>(std::make_shared<Monster::SpikeSlimeM>(offset_x+134.0F, offset_y+RUtil::Random::GetRandomFloat(-4.0F, 4.0F), current_HP)));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Death_lock_action>(shared_from_this(), false));
                break;
            default:
                break;
        }
    }

    void SpikeSlimeL::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=SpikeSlimeLAction::FlameTackle;
        switch(static_cast<SpikeSlimeLAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
            case SpikeSlimeLAction::FlameTackle:
                if(is_last_two_move(SpikeSlimeLAction::FlameTackle))
                    final_next=SpikeSlimeLAction::Lick;
                break;
            case SpikeSlimeLAction::Lick:
                if(!is_last_two_move(SpikeSlimeLAction::Lick))
                    final_next=SpikeSlimeLAction::Lick;
                break;
            default:
                break;
        }

        switch(final_next){
            case SpikeSlimeLAction::FlameTackle:
                set_move(SpikeSlimeLAction::FlameTackle, nullptr, Intent::attack_debuff, FLAME_TACKLE_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case SpikeSlimeLAction::Lick:
                set_move(SpikeSlimeLAction::Lick, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    void SpikeSlimeL::damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared, bool deduct_block){
        Monsters::damage(damage_info, dungeon_shared, deduct_block);
        if(current_HP<=current_max_hp/2 && !is_current_move(SpikeSlimeLAction::Split)){
            set_move(SpikeSlimeLAction::Split, nullptr, Intent::unknown, dungeon_shared.player->get_powers());
            //TODO: interrupted text
        }
    }

    const std::shared_ptr<Draw::ReTexture> &SpikeSlimeL::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Spike Slime/Spike-slime-l-pretty.png");
}

