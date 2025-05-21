#pragma once

#include "Game_object/interface/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID

namespace Card{
namespace Red{
class Clothesline final:public Interface::CardPrototype<Clothesline>
{
public:
    Clothesline():CardPrototype<Clothesline>(RUtil::AtlasRegionID::_red_attack_clothesline, Rarity::common,Type::attack,Color::red,Target::enemy,2,12,0,2){}
    ~Clothesline()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade()override{
        SetDamage(14);
        SetMagicNum(3);
        upgraded=true;
    }
};   
}
} // namespace Card
