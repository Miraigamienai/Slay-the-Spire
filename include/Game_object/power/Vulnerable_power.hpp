#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"

namespace Power{
class Vulnerable_power final : public Powers
{
public:
    Vulnerable_power():Powers(RUtil::Powers_Text_ID::Vulnerable, RUtil::AtlasRegionID::_48_vulnerable, RUtil::AtlasRegionID::_128_vulnerable, PowerType::debuff, true, false){}
    ~Vulnerable_power()override=default;

    float calculate_damage_receive(float damage)const override{
        return damage*1.5F;
    }
    void desc_update()override{
        tip_box.change_body(get_amount_based_desc());
        tip_box.get_body()->set_num_info(Draw::number_info{50, 0, this->amount, Draw::NumStatus::blue});
    }
};   
}