#pragma once

#include <memory>

//fwd decl
namespace Dungeon{
    struct Dungeon_shared;
}
namespace Draw{
    class Draw_2D;
}

namespace Interface{
enum class ScreenType{
    main_dungeon,
    combat_reward,
    grid_cards,
    shop,
    NONE
};

class Is_screen
{
public:
    Is_screen(ScreenType type)noexcept:type(type),on_top(false),on_opening(false),next(ScreenType::NONE){}
    virtual ~Is_screen()=default;
    virtual void update(Dungeon::Dungeon_shared &dungeon_shared)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    void set_on_top(bool value)noexcept{on_top=value;}
    bool is_on_top()const noexcept{return on_top;}
    void set_on_opening()noexcept{on_opening=true;}
    auto get_next()noexcept{return next;}
    const ScreenType type;
protected:
    bool on_top;
    bool on_opening;
    ScreenType next;
};
}