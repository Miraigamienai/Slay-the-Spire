#include "Game_object/character/Monster/Cultist.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    Cultist::Cultist(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<1, CultistAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false){}

    void Cultist::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case CultistAction::Incantation:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Ritual, 3, shared_from_this(), shared_from_this(), true));
                break;
            case CultistAction::DarkStrike:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::slash_horizontal}, dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void Cultist::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=CultistAction::DarkStrike;
        if(!first_move){
            first_move=true;
            final_next=CultistAction::Incantation;
        }

        switch(final_next){
            case CultistAction::Incantation:
                set_move(CultistAction::Incantation, nullptr, Intent::buff, dungeon_shared.player->get_powers());
                break;
            case CultistAction::DarkStrike:
                set_move(CultistAction::DarkStrike, nullptr, Intent::attack, DARK_STRIKE_DAMAGE, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &Cultist::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Cultist/Cultist-pretty.png");
}

