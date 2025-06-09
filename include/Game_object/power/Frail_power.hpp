#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"

namespace Power{
class Frail_power final : public Powers
{
public:
    Frail_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Frail, RUtil::AtlasRegionID::_48_frail, RUtil::AtlasRegionID::_128_frail, PowerType::debuff, true, false, owner_type){}
    ~Frail_power()override=default;

    float calculate_block_modify(float block)const override{
        return block*0.75F;
    }
    
    void desc_update()override{
        tip_box.change_body(get_amount_based_desc());
        tip_box.get_body()->set_num_info(Draw::number_info{0, 0, this->amount, Draw::NumStatus::blue});
    }
};   
}