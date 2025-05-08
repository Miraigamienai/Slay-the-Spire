#pragma once

#include <list>
#include <memory>

#include "Game_object/Group_template.hpp"

//fwd decl
namespace Action{
    class Actions;
}
namespace EffectGen{
    using Effect_gen = Action::Actions;
}
namespace Dungeon{
    struct Dungeon_shared;
}

namespace EffectGen{
class Effect_gen_group final: public Template::Group_template<std::list<std::shared_ptr<Effect_gen>>>
{
public:
    Effect_gen_group()=default;
    ~Effect_gen_group()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared);
};
}