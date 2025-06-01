#include "Game_object/character/Monster/FungiBeast.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    FungiBeast::FungiBeast(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, FungiBeastAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}
    
    void FungiBeast::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case Monster::FungiBeastAction::Bite:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{BITE_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
                break;
            case Monster::FungiBeastAction::Grow:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, 3, shared_from_this(), shared_from_this()));
                break;
            default:
                break;
        }
    }

    void FungiBeast::next_move(RUtil::Random &ai_rng, const Power::Power_group &player_powers){
        auto final_next=FungiBeastAction::Bite;
        switch(static_cast<FungiBeastAction>(dist.NextIndex(ai_rng))){
            case FungiBeastAction::Bite:
                if(!is_last_two_move(FungiBeastAction::Bite))
                    final_next=FungiBeastAction::Grow;
                break;
            case FungiBeastAction::Grow:
                if(!is_current_move(FungiBeastAction::Grow))
                    final_next=FungiBeastAction::Grow;
                break;
            default:
                break;
        }

        switch(final_next){
            case FungiBeastAction::Bite:
                set_move(FungiBeastAction::Bite, nullptr, Intent::attack, BITE_DAMAGE, player_powers);
                break;
            case FungiBeastAction::Grow:
                set_move(FungiBeastAction::Grow, nullptr, Intent::buff, player_powers);
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &FungiBeast::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Fungi Beast/Fungi-beast-pretty.png");
}

