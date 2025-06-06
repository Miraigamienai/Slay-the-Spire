#include "Game_object/character/Monster/SpikeSlimeM.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/action/Show_card_to_discard_action.hpp"
#include "Game_object/card/status/Slimed.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    SpikeSlimeM::SpikeSlimeM(float offset_x, float offset_y, RUtil::Random& rng)
        :SpikeSlimeM(offset_x, offset_y, rng.NextInt(MIN_HP, MAX_HP+1)){}
    
    SpikeSlimeM::SpikeSlimeM(float offset_x, float offset_y, int HP)
        :Abstraction::Monster_move_tracker<2, SpikeSlimeMAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, HP, IMG){}
    
    void SpikeSlimeM::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        switch (current_move()){
            case SpikeSlimeMAction::FlameTackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_discard_action>(std::make_shared<Card::Status::Slimed>(), 1));
                break;
            case SpikeSlimeMAction::Lick:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Frail, 1, shared_from_this(), dungeon_shared.player, true));
                break;
            default:
                break;
        }
    }

    void SpikeSlimeM::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=SpikeSlimeMAction::FlameTackle;
        switch(static_cast<SpikeSlimeMAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
            case SpikeSlimeMAction::FlameTackle:
                if(is_last_two_move(SpikeSlimeMAction::FlameTackle))
                    final_next=SpikeSlimeMAction::Lick;
                break;
            case SpikeSlimeMAction::Lick:
                if(!is_last_two_move(SpikeSlimeMAction::Lick))
                    final_next=SpikeSlimeMAction::Lick;
                break;
            default:
                break;
        }

        switch(final_next){
            case SpikeSlimeMAction::FlameTackle:
                set_move(SpikeSlimeMAction::FlameTackle, nullptr, Intent::attack_debuff, FLAME_TACKLE_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case SpikeSlimeMAction::Lick:
                set_move(SpikeSlimeMAction::Lick, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &SpikeSlimeM::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Spike Slime/Spike-slime-m-pretty.png");
}

