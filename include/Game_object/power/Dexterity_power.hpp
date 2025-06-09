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
        auto &arr=RUtil::Powers_Text_Reader::GetDescriptions(power_id);
        if(amount>=0){
            tip_box.change_body(arr[0]);
            tip_box.get_body()->set_num_info(Draw::number_info{amount, 0, 0, Draw::NumStatus::blue});
        }else{
            tip_box.change_body(arr[1]);
            tip_box.get_body()->set_num_info(Draw::number_info{-amount, 0, 0, Draw::NumStatus::blue});
        }
    }
};   
}