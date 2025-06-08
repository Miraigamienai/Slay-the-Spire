#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Iron_wave final:public Abstraction::CardPrototype<Iron_wave>
{
public:
    Iron_wave():Abstraction::CardPrototype<Iron_wave>(RUtil::AtlasRegionID::_red_attack_iron_wave,RUtil::Cards_Text_ID::Iron_Wave,Rarity::common,Type::attack,Color::red,Target::enemy,1,5,5,0){}

    ~Iron_wave()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(9, for_preview);
    }
private:

};   
}
} // namespace Card
