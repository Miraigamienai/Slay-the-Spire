#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Status{
class Wound final:public Abstraction::CardPrototype<Wound>
{
public:
    Wound():Abstraction::CardPrototype<Wound>(RUtil::AtlasRegionID::_status_wound, RUtil::Cards_Text_ID::Wound, Rarity::common, Type::status, Color::colorless, Target::none, -1, 0, 0, 0){}
    ~Wound()override=default;
    bool CanUse(const Dungeon::Dungeon_shared & /*dungeon_shared */)const override{return false;}
    void Use(Dungeon::Dungeon_shared & /* dungeon_shared */, const std::shared_ptr<Monster::Monsters> & /* target_monster */)override{}
    void Upgrade(bool /* for_preview */)override{}
};   
}
} // namespace Card
