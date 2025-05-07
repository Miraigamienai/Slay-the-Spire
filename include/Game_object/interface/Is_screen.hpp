#pragma once

#include <memory>

//fwd decl
namespace Dungeon{
    class Dungeon_shared;
}
namespace Draw{
    class Draw_2D;
}

namespace Interface{
enum class ScreenType{
    main_dungeon,
    combat_reward,
    grid_cards,
    NONE
};

class Is_screen
{
public:  
    virtual ~Is_screen()=default;
    virtual void update(Dungeon::Dungeon_shared &dungeon_shared)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    void set_on_top(bool value){on_top=value;}
    bool is_on_top()const noexcept{return on_top;}
    void set_on_opening()noexcept{on_opening=true;}
    auto get_next()noexcept{return next;}
protected:
    bool on_top=false;
    bool on_opening=false;
    ScreenType next;
};
}