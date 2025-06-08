#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Inflame final:public Abstraction::CardPrototype<Inflame>
{
public:
    Inflame():Abstraction::CardPrototype<Inflame>(RUtil::AtlasRegionID::_red_power_inflame,RUtil::Cards_Text_ID::Inflame,Rarity::uncommon,Type::power,Color::red,Target::self,1,0,0,2){}

    ~Inflame()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetMagicNum(3, for_preview);
    }
private:

};   
}
} // namespace Card
