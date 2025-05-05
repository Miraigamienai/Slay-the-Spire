#pragma once

namespace RUtil{
class Hitbox{
public:
    Hitbox(float x,float y,float width,float height,bool isCenter=false);
    Hitbox(float width,float height)noexcept
        :x(0.0F),
        y(0.0F),
        width(width),
        height(height),
        cx(0.0F),
        cy(0.0F),
        just_hovered(false),
        hovered(false),
        click_stared(false),
        clicked(false){}

    ~Hitbox()=default;
    const bool&JustHovered()const noexcept{return just_hovered;}
    const bool&Hovered()const noexcept{return hovered;}
    const bool&ClickStarted()const noexcept{return click_stared;}//クリック中も含まれる
    const bool&Clicked()const noexcept{return clicked;}
    void update();
    void resize(float w,float h){
        this->width=w;
        this->height=h;
    }
    void move(float center_x,float center_y)noexcept{
        this->x=center_x-this->width/2.0F;
        this->y=center_y-this->height/2.0F;
    }
    void UnHovered()noexcept{hovered=false;}
    void ResetAll(){just_hovered=hovered=click_stared=clicked=false;}
    float Width()const noexcept{return width;}
    float Height()const noexcept{return height;}
    float CenterX()const noexcept{return cx;}
    float CenterY()const noexcept{return cy;}
private:
    float x,y,width,height;
    float cx,cy;
    bool just_hovered,hovered,click_stared,clicked;
    
    static const int &nx,&ny;
    static const bool &just_clicked,&just_released;
};
}