#include "Game_object/character/Monster/AcidSlimeS.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    AcidSlimeS::AcidSlimeS(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<2, AcidSlimeSAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}

    void AcidSlimeS::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch (current_move()){
            case Monster::AcidSlimeSAction::Lick:
                // Inflict 1  Weak.
                break;
            case Monster::AcidSlimeSAction::Tackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{this->TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void AcidSlimeS::next_move(RUtil::Random &ai_rng, const Power::Power_group &player_powers){
        
    }

    const std::shared_ptr<Draw::ReTexture> &AcidSlimeS::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Acid Slime/Acid-slime-s-pretty.png");
}

