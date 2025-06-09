#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Gain_block_action.hpp"

namespace Power{
class Metallicize_power final : public Powers
{
public:
    Metallicize_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Metallicize, RUtil::AtlasRegionID::_48_armor, RUtil::AtlasRegionID::_128_armor, PowerType::buff, false, false, owner_type){}
    ~Metallicize_power()override=default;

    void at_round_end(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target){
        if(_skip_reduce_once){
            _skip_reduce_once=false;
            return;
        }
        if(target->type == Character::CharacterType::MONSTER){
            this->flash();
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(target, this->amount));
        }
    }
    void desc_update()override{
        auto &arr=RUtil::Powers_Text_Reader::GetDescriptions(power_id);
        if(owner_type==Character::CharacterType::MONSTER) tip_box.change_body(arr[0]);
        else tip_box.change_body(arr[1]);
        tip_box.get_body()->set_num_info(Draw::number_info{0, 0, amount, Draw::NumStatus::blue});
    }
};   
}