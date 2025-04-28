#pragma once

#include <memory>

#include "Game_object/effect/Effect_group.hpp"
#include "Game_object/action/Action_group_handler.hpp"
#include "Game_object/card/Card_group_handler.hpp"
#include "Game_object/dungeon/Overlay.hpp"
#include "Game_object/effect_gen/Effect_gen_group.hpp"
#include "RUtil/Random_package.hpp"

//fwd decl
namespace Character{
    class Player;
}

namespace Dungeon{
struct Dungeon_shared
{
    Effect::Effect_group effs;
    Effect::Effect_group back_effs;
    Effect::Effect_group top_effs;
    EffectGen::Effect_gen_group gen_group;
    Action::Action_group_handler action_group_handler;
    Card::Card_group_handler card_group_handler;
    RUtil::Random_package random_package;
    Overlay overlay;
    std::shared_ptr<Character::Player> player=nullptr;
};
}