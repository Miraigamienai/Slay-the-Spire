#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"

namespace Action{
class Damage_action final:public Actions
{
public:
    Damage_action(int num);
    // Damage_action(int num,const std::shared_ptr<Character::Characters> &target);
    ~Damage_action() override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    int num;
    // std::shared_ptr<Character::Characters> target;
};
}