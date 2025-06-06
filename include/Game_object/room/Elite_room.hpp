#pragma once

#include <memory>

#include "Game_object/room/Monster_room.hpp"

namespace Room{ 
class Elite_room final:public Monster_room
{
public:
    Elite_room(Monster::GroupName group_name)
        :Monster_room(group_name, Room_type::Elite){}
    ~Elite_room()override=default;
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void to_get_reward(Dungeon::Dungeon_shared &dungeon_shared)const override;
private:
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static const std::shared_ptr<Draw::ReTexture> &IMG_O;
};
}