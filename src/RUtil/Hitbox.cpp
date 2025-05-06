#include "RUtil/Hitbox.hpp"
#include "RUtil/Game_Input.hpp"

namespace RUtil{
Hitbox::Hitbox(float x,float y,float width,float height,bool isCenter)
                    :width(width),height(height){
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
    this->just_hovered=this->click_stared=this->clicked=this->hovered=false;
}

void Hitbox::update(){
    using namespace RUtil;
    //hover check
    just_hovered=false;
    if(!hovered) just_hovered=true;
    hovered = x<=Game_Input::getX()&&Game_Input::getX()<=x+width&&y<=Game_Input::getY()&&Game_Input::getY()<=y+height;
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