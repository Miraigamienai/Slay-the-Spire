#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Hemokinesis final:public Abstraction::CardPrototype<Hemokinesis>
{
public:
    Hemokinesis():Abstraction::CardPrototype<Hemokinesis>(RUtil::AtlasRegionID::_red_attack_hemokinesis,RUtil::Cards_Text_ID::Hemokinesis,Rarity::uncommon,Type::attack,Color::red,Target::enemy,1,15,0,2){}

    ~Hemokinesis()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(20, for_preview);
    }
private:

};   
}
} // namespace Card
