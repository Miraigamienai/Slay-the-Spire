#pragma once

#include "Game_object/interface/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Defend final:public Interface::CardPrototype<Defend>
{
public:
    Defend():CardPrototype<Defend>(RUtil::AtlasRegionID::_red_skill_defend,RUtil::Cards_Text_ID::Defend_R,Rarity::basic,Type::skill,Color::red,Target::self,1,0,5,0){}
    ~Defend()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade()override{
        SetBlock(8);
    }
private:
};   
}
} // namespace Card
