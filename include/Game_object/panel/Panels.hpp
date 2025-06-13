#pragma once

#include <memory>

//fwd decl
namespace Draw{
    class Draw_2D;
}
namespace Dungeon{
    struct Dungeon_shared;
}

namespace Panel{
class Panels
{
public:
    Panels(float show_x,float show_y,float hide_x,float hide_y,bool is_hidden)
        :show_x(show_x), show_y(show_y),
        hide_x(hide_x), hide_y(hide_y),
        current_x(is_hidden?hide_x:show_x), current_y(is_hidden?hide_y:show_y),
        target_x(current_x), target_y(current_y),
        _is_hide(is_hidden){}
    virtual ~Panels()=default;
    virtual void update(Dungeon::Dungeon_shared &dungeon_shared)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    void show()noexcept{
        target_x=show_x;
        target_y=show_y;
        _is_hide=false;
    }
    void hide()noexcept{
        target_x=hide_x;
        target_y=hide_y;
        _is_hide=true;
    }
    bool is_hide()const noexcept{return _is_hide;}
protected:
    void update_position();
    const float show_x,show_y,hide_x,hide_y;
    float current_x,current_y;
private:
    float target_x,target_y;
    bool _is_hide;
};
}