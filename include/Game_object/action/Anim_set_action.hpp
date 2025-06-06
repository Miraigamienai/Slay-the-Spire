#pragma once

#include <memory>

#include "Game_object/action/Actions.hpp"//father

//fwd decl
namespace Character{
    class Characters;
    enum class Animation:int;
}

namespace Action{
class Anim_set_action final:public Actions
{
public:
    Anim_set_action(const std::shared_ptr<Character::Characters> &who, Character::Animation anim);
    Anim_set_action(const std::shared_ptr<Character::Characters> &who, Character::Animation anim, float anim_dur, float dur);
    ~Anim_set_action()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    const std::shared_ptr<Character::Characters> who;
    const Character::Animation anim;
    bool anim_once;
    const float anim_dur;
};
}