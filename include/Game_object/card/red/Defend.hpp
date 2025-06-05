#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Defend final:public Abstraction::CardPrototype<Defend>
{
public:
    Defend():CardPrototype<Defend>(RUtil::AtlasRegionID::_red_skill_defend,RUtil::Cards_Text_ID::Defend_R,Rarity::basic,Type::skill,Color::red,Target::self,1,0,5,0){}
    ~Defend()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetBlock(8, for_preview);
    }
private:
};   
}
} // namespace Card
