#include "Game_object/character/Monster/RedLouse.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    RedLouse::RedLouse(float offset_x, float offset_y, RUtil::Random& rng)
    :Abstraction::Monster_move_tracker<2, RedLouseAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
    bite_damage(rng.NextInt(MIN_DAMAGE, MAX_DAMAGE+1)){}

    void RedLouse::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case Monster::RedLouseAction::Grow:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, 3, shared_from_this(), shared_from_this()));
                break;
            case Monster::RedLouseAction::Bite:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{this->bite_damage, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void RedLouse::next_move(RUtil::Random &ai_rng, const Power::Power_group &player_powers){
        auto final_next=RedLouseAction::Bite;
        switch(static_cast<RedLouseAction>(dist.NextIndex(ai_rng))){
            case RedLouseAction::Grow:
                if(!is_last_two_move(RedLouseAction::Grow))
                    final_next=RedLouseAction::Grow;
                break;
            case RedLouseAction::Bite:
                if(is_last_two_move(RedLouseAction::Bite))
                    final_next=RedLouseAction::Grow;
                break;
            default:
                break;
        }

        switch(final_next){
            case RedLouseAction::Grow:
                set_move(RedLouseAction::Grow, nullptr, Intent::buff, player_powers);
                break;
            case RedLouseAction::Bite:
                set_move(RedLouseAction::Bite, nullptr, Intent::attack, bite_damage, player_powers);
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &GreenLouse::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Louses/Louse-red-pretty.png");
}

