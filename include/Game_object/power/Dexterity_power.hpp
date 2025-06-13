#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"

namespace Power{
class Dexterity_power final : public Powers
{
public:
    Dexterity_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Dexterity, RUtil::AtlasRegionID::_48_dexterity, RUtil::AtlasRegionID::_128_dexterity, PowerType::neutral, false, true, owner_type){}
    ~Dexterity_power()override=default;

    float calculate_final_block_modify(float block)const override{
        return block + amount;
    }
    void desc_update()override{
        tip_box.change_body(RUtil::Powers_Text_Reader::GetDescriptions(power_id)[amount>=0 ? 0 : 1]);
    }
    void desc_nums_set()const override{
        tip_box.get_body()->set_num_info(Draw::number_info{0, 0, (amount>=0 ? amount : -amount), Draw::NumStatus::blue});
    }
};   
}