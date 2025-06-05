#pragma once

#include <memory>

#include "Game_object/room/Monster_room.hpp"

namespace Room{ 
class Elite_room final:public Rooms
{
public:
    Elite_room(Monster::GroupName group_name)
        :Rooms(Room_type::Elite),
        monster_room(group_name){}
    ~Elite_room()override=default;
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        monster_room.update(dungeon_shared);
    }
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override{
        monster_room.render(r2);
    }
    void init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color)override{
        monster_room.init_room(dungeon_shared, dungeon_fade_color);
    }
private:
    Monster_room monster_room;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static const std::shared_ptr<Draw::ReTexture> &IMG_O;
};
}