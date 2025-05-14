#pragma once

#include <SDL_stdinc.h>
#include <memory>

//fwd decl
namespace RUtil{
    struct Random_package;
}
namespace Draw{
    class ReTexture;
    class Draw_2D;
}
namespace Dungeon{
    struct Dungeon_shared;        
}

namespace Room{
enum class Room_type{
    Monster,
    Shop,
    Rest,
    Event,
    Treasure,
    Elite
};
enum class Room_phase{
    complete,
    just_complete,
    incomplete
};
class Rooms{
public:
    Rooms(Room_type type)noexcept:room_type(type), room_phase(Room_phase::incomplete){}
    virtual ~Rooms()=default;
    virtual const std::shared_ptr<Draw::ReTexture> &GetTexture()const=0;
    virtual const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    virtual void update(Dungeon::Dungeon_shared &dungeon_shared)=0;
    virtual void init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color)=0;
    const Room_type room_type;
    auto get_phase()const noexcept{return room_phase;}
protected:
    Room_phase room_phase;
    static constexpr float POP_TIME=1.5F;
};
}