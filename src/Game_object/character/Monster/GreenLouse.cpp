#include "Game_object/character/Monster/GreenLouse.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    GreenLouse::GreenLouse(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, GreenLouseAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        bite_damage(rng.NextInt(MIN_DAMAGE, MAX_DAMAGE+1)),
        curl_up_block(rng.NextInt(3, 8)){}
    
    void GreenLouse::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case GreenLouseAction::SpitWeb:
                //TODO:web eff
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, 2, shared_from_this(), dungeon_shared.player, true));
                break;
            case GreenLouseAction::Bite:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void GreenLouse::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=GreenLouseAction::Bite;
        switch(static_cast<GreenLouseAction>(dist.NextIndex(dungeon_shared.random_package.monster_ai_rng))){
            case GreenLouseAction::SpitWeb:
                if(!is_last_two_move(GreenLouseAction::SpitWeb))
                    final_next=GreenLouseAction::SpitWeb;
                break;
            case GreenLouseAction::Bite:
                if(is_last_two_move(GreenLouseAction::Bite))
                    final_next=GreenLouseAction::SpitWeb;
                break;
            default:
                break;
        }

        switch(final_next){
            case GreenLouseAction::SpitWeb:
                set_move(GreenLouseAction::SpitWeb, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
                break;
            case GreenLouseAction::Bite:
                set_move(GreenLouseAction::Bite, nullptr, Intent::attack, bite_damage, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }
    
    void GreenLouse::at_combat_start(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Curl_Up, curl_up_block, shared_from_this(), shared_from_this()));
    }

    const std::shared_ptr<Draw::ReTexture> &GreenLouse::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Louses/Louse-green-pretty.png");
}

