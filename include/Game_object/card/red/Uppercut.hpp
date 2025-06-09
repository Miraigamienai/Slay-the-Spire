#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Uppercut final:public Abstraction::CardPrototype<Uppercut>
{
public:
    Uppercut():Abstraction::CardPrototype<Uppercut>(RUtil::AtlasRegionID::_red_attack_uppercut,RUtil::Cards_Text_ID::Uppercut,Rarity::uncommon,Type::attack,Color::red,Target::enemy,2,13,0,1){
        
    }
    ~Uppercut()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetMagicNum(2, for_preview);
    }
};   
}
} // namespace Card
