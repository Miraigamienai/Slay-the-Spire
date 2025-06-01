#include "Game_object/character/Monster/FatGremlin.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"

namespace Monster{
    FatGremlin::FatGremlin(float offset_x, float offset_y, RUtil::Random& rng)
        :Abstraction::Monster_move_tracker<0, FatGremlinAction>(offset_x, offset_y, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, rng.NextInt(MIN_HP, MAX_HP+1), IMG){}

    void FatGremlin::Action(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{SMASH_DAMAGE, shared_from_this(), AttackType::blunt_light}, dungeon_shared.player));
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Weakened, 1, shared_from_this(), dungeon_shared.player));
    }

    const std::shared_ptr<Draw::ReTexture> &FatGremlin::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Fat-gremlin-pretty.png");
}

