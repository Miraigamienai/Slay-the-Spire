#pragma once

#include "WindowSize.hpp"

namespace RUtil{
//for control offset_y
class Scroll
{
public:
    Scroll(float &offset_y, float &target_offset_y, float bigger_bound, float smaller_bound)
        :offset_y(offset_y),target_offset_y(target_offset_y),bigger_bound(bigger_bound),smaller_bound(smaller_bound),grabbed(false),grabbed_start_y(0.0F){}
    void update();
    ~Scroll()=default;
    bool IsBrabbed()const noexcept{return grabbed;}
    void ChangeSmallerBound(float smaller_bound)noexcept{
        this->smaller_bound=smaller_bound;
    }
    void ChangeBiggerBound(float bigger_bound)noexcept{
        this->bigger_bound=bigger_bound;
    }
private:
    float &offset_y, &target_offset_y;
    float bigger_bound, smaller_bound;
    bool grabbed;
    float grabbed_start_y;

    static constexpr float SCROLL_SPEED=75.0F*Setting::SCALE;
};
}