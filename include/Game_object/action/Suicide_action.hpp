#pragma once

#include "Game_object/action/Actions.hpp"
#include "Game_object/character/Characters.hpp"

namespace Action{
class Suicide_action final:public Actions
{
public:
    Suicide_action(const std::shared_ptr<Character::Characters> &target)noexcept
        :target(target)
    {
        this->duration=DUR;
    }
    ~Suicide_action()override=default;
    void update(Dungeon::Dungeon_shared &/* dungeon_shared */)override{
        if(duration==DUR){
            target->HideHP();
            target->ForceDie();
        }
        TimeGo();
    }
private:
    const std::shared_ptr<Character::Characters> target;

    static constexpr float DUR=1.0F;
};
}