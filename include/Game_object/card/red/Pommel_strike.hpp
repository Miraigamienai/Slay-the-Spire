#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Pommel_strike final:public Abstraction::CardPrototype<Pommel_strike>
{
public:
    Pommel_strike():Abstraction::CardPrototype<Pommel_strike>(RUtil::AtlasRegionID::_red_attack_pommel_strike,RUtil::Cards_Text_ID::Pommel_Strike,Rarity::common,Type::attack,Color::red,Target::enemy,1,9,0,1){}

    ~Pommel_strike()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(10, for_preview);
        SetMagicNum(2, for_preview);
    }
private:

};   
}
} // namespace Card
