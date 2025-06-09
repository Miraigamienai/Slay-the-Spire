#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/power/Strength_power.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Power{
class Anger_power final : public Powers
{
public:
    Anger_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Anger, RUtil::AtlasRegionID::_48_anger, RUtil::AtlasRegionID::_128_anger, PowerType::buff, false, false, owner_type){}
    ~Anger_power()override=default;
    void desc_update()override{
        tip_box.change_body(get_amount_based_desc());
        tip_box.get_body()->set_num_info(Draw::number_info{0, 0, this->amount, Draw::NumStatus::blue});
    }
    void on_use_card(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Card::Cards> &use_card, const std::shared_ptr<Character::Characters> &target)override{
        if(use_card->type==Card::Type::skill){
            this->flash();
            dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, this->amount, target, target));    
        }
    }
};   
}