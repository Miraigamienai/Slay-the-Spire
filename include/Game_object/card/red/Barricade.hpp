#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Barricade final:public Abstraction::CardPrototype<Barricade>
{
public:
    Barricade():Abstraction::CardPrototype<Barricade>(RUtil::AtlasRegionID::_red_power_barricade, RUtil::Cards_Text_ID::Barricade, Rarity::rare, Type::power, Color::red, Target::self, 3, 0, 0, 0){}
    ~Barricade()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetCost(2, for_preview);
    }
};   
}
} // namespace Card
