#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Bash final:public Abstraction::CardPrototype<Bash>
{
public:
    Bash():Abstraction::CardPrototype<Bash>(RUtil::AtlasRegionID::_red_attack_bash,RUtil::Cards_Text_ID::Bash,Rarity::basic,Type::attack,Color::red,Target::enemy,2,8,0,2){
        this->exhaust=true;
    }
    ~Bash()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(10, for_preview);
        SetMagicNum(3, for_preview);
    }
};   
}
} // namespace Card
