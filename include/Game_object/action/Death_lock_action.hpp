#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/character/Characters.hpp"

namespace Action{
class Death_lock_action final:public Actions
{
public:
    Death_lock_action(const std::shared_ptr<Character::Characters> &target, bool lock)noexcept
        :target(target), lock(lock){}
    ~Death_lock_action()override=default;
    void update(Dungeon::Dungeon_shared &/* dungeon_shared */)override{
        target->DeathLock(lock);
        is_done=true;
    }
private:
    const std::shared_ptr<Character::Characters> target;
    const bool lock;
};
}