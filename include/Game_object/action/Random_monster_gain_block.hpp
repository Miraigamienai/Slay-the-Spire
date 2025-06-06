#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"//father

//fwd decl
namespace Character{
    class Characters;
}

namespace Action{
class Random_monster_gain_block final:public Actions
{
public:
    Random_monster_gain_block(const std::shared_ptr<Character::Characters> &src, int amt);
    ~Random_monster_gain_block()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    const std::shared_ptr<Character::Characters> src;
    const int amt;

    static constexpr float DUR=0.5F;
};
}