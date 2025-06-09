#include "Game_object/character/Monster/Sentry.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"

namespace Monster{
    Sentry::Sentry(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, SentryAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false)
        {
            counter++;
            if(counter%3%2==0)
                is_second=true;
        }
    
    void Sentry::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case SentryAction::Beam:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{this->BEAM_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
                break;
            case SentryAction::Bolt:
                //Shuffles 2 Dazed into the discard pile.
                break;
            default:
                break;
        }
    }

    void Sentry::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=SentryAction::Bolt;
        if(is_second){
            final_next=SentryAction::Beam;
        }
        if(!first_move){
            first_move=true;
        }else{
            switch(static_cast<SentryAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
                case SentryAction::Bolt:
                    final_next=SentryAction::Beam;
                    break;
                case SentryAction::Beam:
                    final_next=SentryAction::Bolt;
                    break;
                default:
                    break;
            }
        }
        switch(final_next){
            case SentryAction::Beam:
                set_move(SentryAction::Beam, nullptr, Intent::attack, BEAM_DAMAGE, dungeon_shared.player->get_powers());
                break;
            case SentryAction::Bolt:
                set_move(SentryAction::Bolt, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
                break;

            default:
                break;
        }
    }
    int Sentry::counter=0;
    const std::shared_ptr<Draw::ReTexture> &Sentry::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Sentry/Sentry-pretty.png");
}

