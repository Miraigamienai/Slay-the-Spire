#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"

namespace Power{
class Split_power final : public Powers
{
public:
    Split_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Split, RUtil::AtlasRegionID::_48_split, RUtil::AtlasRegionID::_128_split, PowerType::buff, false, false, owner_type){
        this->amount=NO_DISPLAY_AMOUNT;
    }
    ~Split_power()override=default;
};   
}