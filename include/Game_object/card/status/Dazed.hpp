#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Status{
class Dazed final:public Abstraction::CardPrototype<Dazed>
{
public:
    Dazed():Abstraction::CardPrototype<Dazed>(RUtil::AtlasRegionID::_status_dazed, RUtil::Cards_Text_ID::Dazed, Rarity::common, Type::status, Color::colorless, Target::none, -1, 0, 0, 0){
        ethereal=true;
    }
    ~Dazed()override=default;
    void Use(Dungeon::Dungeon_shared &/* dungeon_shared */, const std::shared_ptr<Monster::Monsters> &/* target_monster */)override{};
    void Upgrade(bool /* for_preview */)override{}
    bool CanUse(const Dungeon::Dungeon_shared &/* dungeon_shared */)const override{return false;}
};
}
} // namespace Card
