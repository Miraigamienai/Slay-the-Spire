#pragma once

#include <memory>

//fwd decl
namespace Dungeon{
    struct Dungeon_shared;
}
namespace Draw{
    class Draw_2D;
}

namespace Abstraction{
enum class ScreenType{
    main_dungeon,
    combat_reward,
    grid_cards,
    shop,
    death,
    NONE
};

class Is_screen
{
public:
    Is_screen(ScreenType type)noexcept:type(type),on_top(false){}
    virtual ~Is_screen()=default;
    virtual void update(Dungeon::Dungeon_shared &dungeon_shared)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    void set_on_top(bool value)noexcept{on_top=value;}
    bool is_on_top()const noexcept{return on_top;}
    const ScreenType type;
protected:
    bool on_top;
};
}