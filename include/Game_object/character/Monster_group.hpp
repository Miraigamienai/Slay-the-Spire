#pragma once

#include <vector>
#include <memory>

#include "Game_object/Group_template.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
}
namespace Monster{
    class Monsters;
}
namespace Dungeon{
    class Dungeon_shared;
}

namespace Monster{
class Monster_group final:public Template::Group_template<std::vector<std::shared_ptr<Monsters>>>
{
public:
    Monster_group()=default;
    ~Monster_group()=default;
    std::shared_ptr<Monsters> GetHoveredMonster()const;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update();
    void at_turn_end(Dungeon::Dungeon_shared &dungeon_shared);
    bool IsAllDie()const;
};
}