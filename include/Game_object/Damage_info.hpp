#pragma once

#include <memory>

//fwd decl
namespace Character{
    class Characters;
}

enum class AttackType:int{
    shield,
    slash_diagonal,
    slash_heavy,
    slash_horizontal,
    slash_vertical,
    blunt_light,
    blunt_heavy,
    fire,
    poison,
    NONE
};

struct Damage_info
{
    int dmg;
    std::shared_ptr<Character::Characters> src;
    AttackType attack_type; 
};
