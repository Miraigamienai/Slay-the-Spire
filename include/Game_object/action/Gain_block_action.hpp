#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"

namespace Character{
    class Characters;
}

namespace Action{
class Gain_block_action final:public Actions
{
public:
    Gain_block_action(const std::shared_ptr<Character::Characters> &target,int amount);
    ~Gain_block_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    std::shared_ptr<Character::Characters> target;
    int amount;
};
}
