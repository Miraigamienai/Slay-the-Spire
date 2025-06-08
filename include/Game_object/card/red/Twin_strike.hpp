#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Twin_strike final:public Abstraction::CardPrototype<Twin_strike>
{
public:
    Twin_strike():Abstraction::CardPrototype<Twin_strike>(RUtil::AtlasRegionID::_red_attack_twin_strike,RUtil::Cards_Text_ID::Strike_R,Rarity::common,Type::attack,Color::red,Target::enemy,1,5,0,0){}

    ~Twin_strike()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(7, for_preview);
    }
private:

};   
}
} // namespace Card
