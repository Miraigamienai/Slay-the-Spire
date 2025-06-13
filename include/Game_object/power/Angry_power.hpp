#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Power{
class Angry_power final : public Powers
{
public:
    Angry_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Angry, RUtil::AtlasRegionID::_48_anger, RUtil::AtlasRegionID::_128_anger, PowerType::buff, false, false, owner_type){}
    ~Angry_power()override=default;
    void on_attacked(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target, int fixed_dmg)override{
        if(fixed_dmg>0){
            this->flash();
            dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, this->amount, target, target));
        }
    }
};   
}