#pragma once

#include <memory>

#include "Game_object/room/rooms.hpp"
#include "Game_object/character/Monster_group.hpp"//monsters

//fwd decl
namespace Monster{
    enum class GroupName:int;
    class Monster_group;
}

namespace Room{
//need:Monster Player Cards BattleManage
class Monster_room:public Rooms
{
public:
    Monster_room();
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void init_room(RUtil::Random_package &random_package)override;
    void set_monster_group_name(Monster::GroupName group_name)noexcept{m_group_name=group_name;}
private:
    void prepare_to_battle();
    float m_wait_timer;
    Monster::GroupName m_group_name;
    Monster::Monster_group m_monsters;

    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static const std::shared_ptr<Draw::ReTexture> &IMG_O;
};
}