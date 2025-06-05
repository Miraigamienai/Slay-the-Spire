#pragma once

#include <memory>

//fwd decl 
namespace Dungeon{
    class Dungeon_shared;
}

namespace Monster{
enum class GroupName:int{
    //exordium
    //weak
    Cultist,
    Jaw_Worm,
    _2_Louse,
    Small_Slimes,
    //strong
    Blue_Slaver,
    Gremlin_Gang,
    Looter,
    Large_Slime,
    Lots_of_Slimes,
    Exordium_Thugs, 
    Exordium_Wildlife,
    Red_Slaver,
    _3_Louse,
    _2_Fungi_Beasts,

    None
};

class Monster_group_creater
{
public:
    Monster_group_creater()=delete;~Monster_group_creater()=delete;Monster_group_creater(const Monster_group_creater &) = delete;Monster_group_creater(Monster_group_creater &&) = delete;Monster_group_creater &operator=(const Monster_group_creater &) = delete;Monster_group_creater &operator=(Monster_group_creater &&) = delete;
    
    static void CreateGroup(Dungeon::Dungeon_shared& dungeon_shared, GroupName group_name);
};
}
