#pragma once

#include "Game_object/power/Powers.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Characters.hpp"
#include "Game_object/action/Remove_power_action.hpp"
#include "RUtil/All_Image.hpp"

namespace Power{
class Entangled_power final : public Powers
{
public:
    Entangled_power(Character::CharacterType owner_type):Powers(RUtil::Powers_Text_ID::Entangled, RUtil::AtlasRegionID::_48_entangle, RUtil::AtlasRegionID::_128_entangle, PowerType::debuff, false, false, owner_type){
        amount=NO_DISPLAY_AMOUNT;
    }
    ~Entangled_power()override=default;
    bool check_card_can_use(const std::shared_ptr<const Card::Cards> &card)const{
        return card->type != Card::Type::attack;
    }
    void at_turn_end(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target)override{
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Remove_power_action>(shared_from_this(), target));
    };
};   
}