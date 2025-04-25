#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"
#include "Game_object/Damage_info.hpp"

//fwd decl
namespace Character{
    class Characters;
}

namespace Action{
class Damage_action final:public Actions
{
public:
    Damage_action(const Damage_info&damage_info,const std::shared_ptr<Character::Characters> &target=nullptr);
    ~Damage_action() override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    Damage_info damage_info;
    std::shared_ptr<Character::Characters> target;
};
}