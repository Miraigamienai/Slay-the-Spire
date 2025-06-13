#pragma once

#include "Game_object/power/Powers.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Remove_power_action.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"

namespace Power{
class Curl_up_power final : public Powers
{
public:
    Curl_up_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Curl_Up, RUtil::AtlasRegionID::_48_closeUp, RUtil::AtlasRegionID::_128_closeUp, PowerType::buff, false, false, owner_type), trigger(false){}
    ~Curl_up_power()override=default;
    void on_attacked(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target, int fixed_dmg)override{
        if(!trigger && fixed_dmg<target->GetCurrentHP() && fixed_dmg>0){
            trigger=true;
            this->flash();
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(target, this->amount));
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Remove_power_action>(shared_from_this(), target));
        }
    }
private:
    bool trigger;
};   
}