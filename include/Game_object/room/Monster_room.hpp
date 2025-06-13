#pragma once

#include <memory>

#include "Game_object/room/Rooms"
#include "Game_object/button/End_turn_button.hpp"

//fwd decl
namespace Monster{
    enum class GroupName:int;
}
namespace Character{
    class Characters;
}

namespace Room{
//need:Monster Player Cards 
class Monster_room:public Rooms
{
public:
    Monster_room(Monster::GroupName group_name);
    ~Monster_room()override=default;
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void render_higher(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color)override;
    void set_monster_group_name(Monster::GroupName group_name)noexcept{m_group_name=group_name;}
    Monster::GroupName m_group_name;
protected:
    Monster_room(Monster::GroupName group_name, Room_type type);
    virtual void to_get_reward(Dungeon::Dungeon_shared &dungeon_shared)const;
private:
    Button::End_turn_button end_turn_button;
    float m_wait_timer;
    bool ending_battle;
    float ending_battle_timer;
    Uint32 dungeon_fade_color;
    std::shared_ptr<Character::Characters> tip_character;
    int turn_count;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static const std::shared_ptr<Draw::ReTexture> &IMG_O;
};
}