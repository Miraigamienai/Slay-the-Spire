#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Status{
class Slimed final:public Abstraction::CardPrototype<Slimed>
{
public:
    Slimed():Abstraction::CardPrototype<Slimed>(RUtil::AtlasRegionID::_status_slimed, RUtil::Cards_Text_ID::Slimed, Rarity::common, Type::status, Color::colorless, Target::self, 1, 0, 0, 0){}
    ~Slimed()override=default;
    void Use(Dungeon::Dungeon_shared &/* dungeon_shared */, const std::shared_ptr<Monster::Monsters> &/* target_monster */)override{};
    void Upgrade(bool /* for_preview */)override{}
};   
}
} // namespace Card
