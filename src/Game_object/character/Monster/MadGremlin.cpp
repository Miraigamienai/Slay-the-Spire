#include "Game_object/character/Monster/MadGremlin.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"

namespace Monster{
    MadGremlin::MadGremlin(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<0, MadGremlinAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}
    
    void MadGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{SCRATCH_DAMAGE, shared_from_this(), AttackType::slash_diagonal}, dungeon_shared.player));
    }

    const std::shared_ptr<Draw::ReTexture> &MadGremlin::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Mad-gremlin-pretty.png");
}

