#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Shockwave final:public Abstraction::CardPrototype<Shockwave>
{
public:
    Shockwave():Abstraction::CardPrototype<Shockwave>(RUtil::AtlasRegionID::_red_skill_shockwave,RUtil::Cards_Text_ID::Shockwave,Rarity::uncommon,Type::skill,Color::red,Target::all_enemy,2,0,0,3){
        this->exhaust=true;
    }
    ~Shockwave()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetMagicNum(5, for_preview);
    }
};   
}
} // namespace Card
