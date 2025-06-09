#include "Game_object/character/Monster/Sentry.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
// #include "Game_object/action/Gain_block_action.hpp"
// #include "Game_object/action/Anim_set_action.hpp"
// #include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "Game_object/effect_gen/Shockwave_gen.hpp"
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
        if(is_current_bolt){
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Shockwave_gen>(GetcX(), GetcY(), RUtil::ToRGBA(RUtil::Colors::ROYAL_BLUE)), 0.5F));
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_discard_action>(std::make_shared<Card::Status::Dazed>(), 2));
        }else{

        }
    
        is_current_bolt=!is_current_bolt;
    }

    void Sentry::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        if(is_current_bolt)
            set_move(SentryAction::Bolt, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
        else
            set_move(SentryAction::Beam, nullptr, Intent::attack, BEAM_DAMAGE, dungeon_shared.player->get_powers());
    }

    const std::shared_ptr<Draw::ReTexture> &Sentry::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Sentry/Sentry-pretty.png");
}

