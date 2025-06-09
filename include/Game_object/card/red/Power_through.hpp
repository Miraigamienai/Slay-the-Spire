#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Power_through final:public Abstraction::CardPrototype<Power_through>
{
public:
    Power_through():Abstraction::CardPrototype<Power_through>(RUtil::AtlasRegionID::_red_skill_power_through,RUtil::Cards_Text_ID::Power_Through,Rarity::uncommon,Type::skill,Color::red,Target::self,1,0,15,2){}

    ~Power_through()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetBlock(20, for_preview);
    }
private:

};   
}
} // namespace Card
