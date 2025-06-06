#include "Game_object/character/Monster/AcidSlimeS.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    AcidSlimeS::AcidSlimeS(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<1, AcidSlimeSAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG),
        first_move(false){}

    void AcidSlimeS::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        switch (current_move()){
            case AcidSlimeSAction::Lick:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, 1, shared_from_this(), dungeon_shared.player, true));
                break;
            case AcidSlimeSAction::Tackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
                break;
            default:
                break;
        }
    }

    void AcidSlimeS::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        auto final_next=AcidSlimeSAction::Lick;
        if(!first_move){
            first_move=true;
            if(dungeon_shared.random_package.monster_ai_rng.Nextboolean()) final_next=AcidSlimeSAction::Tackle;
        }else{
            if(is_current_move(AcidSlimeSAction::Lick)) final_next=AcidSlimeSAction::Tackle;
        }

        switch(final_next){
            case AcidSlimeSAction::Lick:
                set_move(AcidSlimeSAction::Lick, nullptr, Intent::debuff, dungeon_shared.player->get_powers());
                break;
            case AcidSlimeSAction::Tackle:
                set_move(AcidSlimeSAction::Tackle, nullptr, Intent::attack, TACKLE_DAMAGE, dungeon_shared.player->get_powers());
                break;
            default:
                break;
        }
    }

    const std::shared_ptr<Draw::ReTexture> &AcidSlimeS::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Acid Slime/Acid-slime-s-pretty.png");
}

