#include "RUtil/Hitbox.hpp"
#include "RUtil/Game_Input.hpp"

namespace RUtil{
Hitbox::Hitbox(float x,float y,float width,float height,bool isCenter)noexcept
    :width(width),
    height(height),
    just_hovered(false),
    hovered(false),
    click_stared(false),
    clicked(false)
{
    if(isCenter){
        this->cx=x;
        this->cy=y;
        this->x=x-width/2.0F;
        this->y=y-height/2.0F;
    }else{
        this->cx=x+width/2.0F;
        this->cy=y+height/2.0F;
        this->x=x;
        this->y=y;
    }
}

void Hitbox::update(){
    using namespace RUtil;
    //hover check
    just_hovered=false;
    if(!hovered) just_hovered=true;
    hovered = x<=static_cast<float>(Game_Input::getX())&&static_cast<float>(Game_Input::getX())<=x+width&&y<=static_cast<float>(Game_Input::getY())&&static_cast<float>(Game_Input::getY())<=y+height;
    if(!hovered) just_hovered=false;
    //click check
    if(hovered&&Game_Input::just_clicked()){
        this->click_stared=true;
    }else if(clicked){
        clicked=false;
    }else if(click_stared&&Game_Input::just_released()){
        click_stared=false;
        if(hovered) clicked=true;
    }
}
}