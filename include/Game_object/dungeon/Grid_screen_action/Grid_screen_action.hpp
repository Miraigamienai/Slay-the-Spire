#pragma once

#include <memory>

//fwd decl
namespace Card{
    class Cards;
}
namespace Dungeon{
    class Dungeon_shared;
}
namespace Draw{
    class Draw_2D;
}

namespace Dungeon{
namespace GridScreenAction{
class Grid_screen_action
{
public:
    Grid_screen_action(bool have_cancel_button)noexcept:have_cancel_button(have_cancel_button),is_done(false),is_cancelled(false){};
    virtual ~Grid_screen_action()=default;
    virtual void SetCard(const std::shared_ptr<Card::Cards> &card)=0;
    virtual void update(Dungeon::Dungeon_shared &dungeon_shared)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    
    bool IsDone()const noexcept{return is_done;}
    bool IsCancelled()const noexcept{return is_cancelled;}
    const bool have_cancel_button;
protected:
    bool is_done;
    bool is_cancelled;

    void render_two_card(const std::shared_ptr<Draw::Draw_2D> &r2, const std::shared_ptr<Card::Cards> &card1, const std::shared_ptr<Card::Cards> &card2)const;
    void render_dark_cover(const std::shared_ptr<Draw::Draw_2D> &r2)const;
};
}
}