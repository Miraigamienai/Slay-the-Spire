#pragma once

#include "Game_object/interface/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID

namespace Card{
namespace Red{
class Defend final:public Interface::CardPrototype<Defend>
{
public:
    Defend():CardPrototype<Defend>(RUtil::AtlasRegionID::_red_skill_defend,Rarity::basic,Type::skill,Color::red,Target::self,1,0,5,0){}
    ~Defend()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade()override{
        SetDefense(8);
        upgraded=true;
    }
private:
};   
}
} // namespace Card
