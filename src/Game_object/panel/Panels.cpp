#include "Game_object/panel/Panels.hpp"
#include "RUtil/Some_Math.hpp"

namespace Panel{
    void Panels::update_position(){
        current_x=RUtil::Math::varlerp(current_x,target_x,7.0F,0.5F);
        current_y=RUtil::Math::varlerp(current_y,target_y,7.0F,0.5F);
    }
}