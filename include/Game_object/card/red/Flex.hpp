#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Flex final:public Abstraction::CardPrototype<Flex>
{
public:
    Flex():Abstraction::CardPrototype<Flex>(RUtil::AtlasRegionID::_red_skill_flex,RUtil::Cards_Text_ID::Flex,Rarity::basic,Type::skill,Color::red,Target::self,0,0,0,2){}

    ~Flex()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetMagicNum(4, for_preview);
    }
private:

};   
}
} // namespace Card
