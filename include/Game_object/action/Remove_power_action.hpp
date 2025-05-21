#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"
#include "Game_object/power/Powers.hpp"

namespace Character{
    class Characters;
}

namespace Action{
class Remove_power_action final:public Actions
{
public:
    Remove_power_action(const std::shared_ptr<Power::Powers> &power, const std::shared_ptr<Character::Characters> &target)noexcept
        :power(power),
        target(target)
    {
        this->duration=ACTION_DUR_XFAST;
    }
    ~Remove_power_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    std::shared_ptr<Power::Powers> power;
    std::shared_ptr<Character::Characters> target;
};
}