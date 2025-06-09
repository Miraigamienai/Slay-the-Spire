#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Bloodletting final:public Abstraction::CardPrototype<Bloodletting>
{
public:
    Bloodletting():Abstraction::CardPrototype<Bloodletting>(RUtil::AtlasRegionID::_red_skill_bloodletting,RUtil::Cards_Text_ID::Bloodletting,Rarity::uncommon,Type::skill,Color::red,Target::self,0,3,0,2){}

    ~Bloodletting()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetMagicNum(3, for_preview);
    }
private:

};   
}
} // namespace Card
