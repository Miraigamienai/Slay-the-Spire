#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"

namespace Power{
class Barricade_power final : public Powers
{
public:
    Barricade_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Barricade, RUtil::AtlasRegionID::_48_barricade, RUtil::AtlasRegionID::_128_barricade, PowerType::buff, false, false, owner_type){
        this->amount=NO_DISPLAY_AMOUNT;
    }
    ~Barricade_power()override=default;
};   
}