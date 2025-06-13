#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"

namespace Power{
class Mode_shift_power final : public Powers
{
public:
    Mode_shift_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Mode_Shift, RUtil::AtlasRegionID::_48_modeShift, RUtil::AtlasRegionID::_128_modeShift, PowerType::buff, false, false, owner_type){}
    ~Mode_shift_power()override=default;
};   
}