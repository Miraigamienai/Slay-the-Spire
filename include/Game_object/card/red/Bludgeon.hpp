#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Bludgeon final:public Abstraction::CardPrototype<Bludgeon>
{
public:
    Bludgeon():Abstraction::CardPrototype<Bludgeon>(RUtil::AtlasRegionID::_red_attack_bludgeon,RUtil::Cards_Text_ID::Bludgeon,Rarity::rare,Type::attack,Color::red,Target::enemy,3,32,0,0){}

    ~Bludgeon()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(42, for_preview);
    }
private:

};   
}
} // namespace Card
