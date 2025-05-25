#pragma once

#include <memory>

#include "Game_object/room/rooms.hpp"

//fwd decl
namespace Monster{
    enum class GroupName:int;
}

namespace Room{
//need:Monster Player Cards 
class Elite_room final:public Rooms
{
public:
    Elite_room();
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color)override;
    void set_monster_group_name(Monster::GroupName group_name)noexcept{m_group_name=group_name;}
private:
    float m_wait_timer;
    Monster::GroupName m_group_name;
    bool ending_battle;
    float ending_battle_timer;

    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static const std::shared_ptr<Draw::ReTexture> &IMG_O;
};
}