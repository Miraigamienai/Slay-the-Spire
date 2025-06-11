#pragma once

#include "Game_object/power/Powers.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Text_layout.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Damage_action.hpp"

namespace Power{
class Sharp_hide_power final : public Powers
{
public:
    Sharp_hide_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Sharp_Hide, RUtil::AtlasRegionID::_48_sharpHide, RUtil::AtlasRegionID::_128_sharpHide, PowerType::buff, false, false, owner_type){}
    ~Sharp_hide_power()override=default;
    void desc_update()override{
        tip_box.change_body(get_amount_based_desc());
        tip_box.get_body()->set_num_info(Draw::number_info{0, 0, this->amount, Draw::NumStatus::blue});
    }
    void on_use_card(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Card::Cards> &use_card, const std::shared_ptr<Character::Characters> &target)override{
        if(use_card->type==Card::Type::attack){
            this->flash();
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{this->amount, target, AttackType::slash_horizontal}, dungeon_shared.player));
        }
    }
};   
}