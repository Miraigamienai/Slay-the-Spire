#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"
#include "Game_object/power/Powers.hpp"

namespace Character{
    class Characters;
}

namespace Action{
class Reduce_power_action final:public Actions
{
public:
    Reduce_power_action(const std::shared_ptr<Power::Powers> &power, const std::shared_ptr<Character::Characters> &target, int amount=1)noexcept
        :power(power),
        target(target),
        amount(amount)
    {
        this->duration=ACTION_DUR_FAST;
    }
    ~Reduce_power_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    std::shared_ptr<Power::Powers> power;
    std::shared_ptr<Character::Characters> target;
    int amount;
};
}