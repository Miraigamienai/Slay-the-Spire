#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/power/Strength_power.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Power{
class Ritual_power final : public Powers
{
public:
    Ritual_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Ritual, RUtil::AtlasRegionID::_48_ritual, RUtil::AtlasRegionID::_128_ritual, PowerType::buff, false, false, owner_type){}
    ~Ritual_power()override=default;

    void at_round_end(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target){
        if(_skip_reduce_once){
            _skip_reduce_once=false;
            return;
        }
        if(target->type == Character::CharacterType::MONSTER){
            this->flash();
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, this->amount, target, target));
        }   
    }
    void desc_update()override{
        auto &arr=RUtil::Powers_Text_Reader::GetDescriptions(power_id);
        if(owner_type==Character::CharacterType::MONSTER){
            tip_box.change_body(arr[0]);
            tip_box.get_body()->set_num_info(Draw::number_info{amount, 0, 0, Draw::NumStatus::blue});
        }else{
            tip_box.change_body(arr[1]);
            tip_box.get_body()->set_num_info(Draw::number_info{-amount, 0, 0, Draw::NumStatus::blue});
        }
    }
};   
}