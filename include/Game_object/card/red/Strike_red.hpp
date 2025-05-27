#pragma once

#include "Game_object/interface/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Strike_red final:public Interface::CardPrototype<Strike_red>
{
public:
    Strike_red():Interface::CardPrototype<Strike_red>(RUtil::AtlasRegionID::_red_attack_strike,RUtil::Cards_Text_ID::Strike_R,Rarity::basic,Type::attack,Color::red,Target::enemy,1,6,0,0){}

    ~Strike_red()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(9, for_preview);
    }
private:

};   
}
} // namespace Card
