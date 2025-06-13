#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Reduce_power_action.hpp"

namespace Power{
class Artifact_power final : public Powers
{
public:
    Artifact_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Artifact, RUtil::AtlasRegionID::_48_artifact, RUtil::AtlasRegionID::_128_artifact, PowerType::buff, false, false, owner_type){}
    bool on_power_applied(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Powers> &applied_power, const std::shared_ptr<Character::Characters> &target)override{
        if(applied_power->power_type == Power::PowerType::debuff || (applied_power->power_type == Power::PowerType::neutral && applied_power->get_amount() < 0)){
            dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Reduce_power_action>(shared_from_this(), target));
            return true;
        }
        return false;
    }
    ~Artifact_power()override=default;
};   
}