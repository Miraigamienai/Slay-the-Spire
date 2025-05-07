#include "RUtil/Scroll.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Game_Input.hpp"

namespace RUtil{
    void Scroll::update(){
        //target_offset_y update
        if(grabbed){
            if(Game_Input::is_down())
                target_offset_y=static_cast<float>(Game_Input::getY())-grabbed_start_y;
            else
                grabbed=false;
        }else{
            if(Game_Input::is_scroll_down())
                target_offset_y+=this->SCROLL_SPEED;
            else if(RUtil::Game_Input::is_scroll_up())
                target_offset_y-=this->SCROLL_SPEED;

            if (RUtil::Game_Input::just_clicked()) {
                grabbed = true;
                grabbed_start_y = static_cast<float>(RUtil::Game_Input::getY()) - target_offset_y;
            }
        }

        //target bound check
        if(bigger_bound < target_offset_y)
            target_offset_y=RUtil::Math::scrolllerp(target_offset_y, bigger_bound);
        else if(smaller_bound > target_offset_y)
            target_offset_y=RUtil::Math::scrolllerp(target_offset_y, smaller_bound);

        //lerp y to target_y
        offset_y=RUtil::Math::fadelerp(offset_y,target_offset_y);
    }   
}