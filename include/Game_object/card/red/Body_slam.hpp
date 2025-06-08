#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Body_slam final:public Abstraction::CardPrototype<Body_slam>
{
public:
    Body_slam():Abstraction::CardPrototype<Body_slam>(RUtil::AtlasRegionID::_red_attack_body_slam,RUtil::Cards_Text_ID::Body_Slam,Rarity::basic,Type::attack,Color::red,Target::enemy,1,6,0,0){}

    ~Body_slam()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(9, for_preview);
    }
private:

};   
}
} // namespace Card
