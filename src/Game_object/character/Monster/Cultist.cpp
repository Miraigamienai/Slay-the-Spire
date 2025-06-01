#include "Game_object/character/Monster/Cultist.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    Cultist::Cultist(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<1, CultistAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false){}

    void Cultist::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case Monster::CultistAction::Incantation:
                //Gains 3  Ritual(strength).
                break;
            case Monster::CultistAction::DarkStrike:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{DARK_STRIKE_DAMAGE, shared_from_this(), AttackType::slash_horizontal}, dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void Cultist::next_move(RUtil::Random &ai_rng, const Power::Power_group &player_powers){
        auto final_next=CultistAction::DarkStrike;
        if(!first_move){
            first_move=true;
            final_next=CultistAction::Incantation;
        }

        switch(final_next){
            case CultistAction::Incantation:
                set_move(CultistAction::Incantation, nullptr, Intent::buff, player_powers);
                break;
            case CultistAction::DarkStrike:
                set_move(CultistAction::DarkStrike, nullptr, Intent::attack, DARK_STRIKE_DAMAGE, player_powers);
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &Cultist::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Cultist/Cultist-pretty.png");
}

