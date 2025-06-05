#include "Game_object/character/Monster/SpikeSlimeS.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    SpikeSlimeS::SpikeSlimeS(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<0, SpikeSlimeSAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}

    void SpikeSlimeS::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_FAST));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));
    }

    const std::shared_ptr<Draw::ReTexture> &SpikeSlimeS::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Spike Slime/Spike-slime-s-pretty.png");
}

