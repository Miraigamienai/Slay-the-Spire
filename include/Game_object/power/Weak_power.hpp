#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"

namespace Power{
class Weak_power final : public Powers
{
public:
    Weak_power():Powers(RUtil::Powers_Text_ID::Weakened, RUtil::AtlasRegionID::_48_weak, RUtil::AtlasRegionID::_128_weak, PowerType::debuff, true){}
    ~Weak_power()override=default;

    float calculate_damage_dealt(float damage)const override{
        return damage*0.75F;
    }
    void desc_update()override; 
};   
}