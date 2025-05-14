#ifndef BASIC_PANEL_HPP
#define BASIC_PANEL_HPP
#include <memory>
#include "Draw/Draw_2D.hpp"
#include "RUtil/Hitbox.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
namespace TopPanel
{
class Basic_panel
{

public:
    Basic_panel(float x,float y,float w,float h):hitbox(x,y,w,h){};
    ~Basic_panel()=default;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    virtual void update(Dungeon::Dungeon_shared &dungeon_shared)=0;
    
protected:
    RUtil::Hitbox hitbox;
};
}

#endif