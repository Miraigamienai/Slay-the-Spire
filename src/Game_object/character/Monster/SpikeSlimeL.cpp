#include "Game_object/character/Monster/SpikeSlimeL.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    SpikeSlimeL::SpikeSlimeL(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, SpikeSlimeLAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}
    
    void SpikeSlimeL::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case SpikeSlimeLAction::FlameTackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{FLAME_TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                //TODO: shuffles 2 Slimed into the discard pile.
                break;
            case SpikeSlimeLAction::Lick:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Frail, 2, shared_from_this(), dungeon_shared.player, true));
                break;
            case SpikeSlimeLAction::Split:
                //TODO: spawn 2 Spike Slime M.
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

    const std::shared_ptr<Draw::ReTexture> &SpikeSlimeL::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Spike Slime/Spike-slime-l-pretty.png");
}

