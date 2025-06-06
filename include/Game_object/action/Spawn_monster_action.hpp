#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Action{
class Spawn_monster_action final:public Actions
{
public:
    Spawn_monster_action(const std::shared_ptr<Monster::Monsters> &target)noexcept
        :target(target)
    {
        this->duration=DUR;
    }
    ~Spawn_monster_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(duration==DUR){
            target->next_move(dungeon_shared);
            target->ShowHP();
            dungeon_shared.room_monsters.AddTop(target);
        }
        TimeGo();
    }
private:
    const std::shared_ptr<Monster::Monsters> target;

    static constexpr float DUR=0.1F;
};
}