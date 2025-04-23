#pragma once

#include "Game_object/action/Actions.hpp"

namespace Action{
class Wait_action final:public Actions
{
public:
    Wait_action(float dur)noexcept{this->duration=dur;}
    ~Wait_action()override=default;
    void update(Dungeon::Dungeon_shared &/* dungeon_shared */)
        noexcept(noexcept(TimeGo())) override  
    {
        TimeGo();
    }

};
}