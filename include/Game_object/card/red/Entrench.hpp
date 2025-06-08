#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Entrench final:public Abstraction::CardPrototype<Entrench>
{
public:
    Entrench():CardPrototype<Entrench>(RUtil::AtlasRegionID::_red_skill_entrench,RUtil::Cards_Text_ID::Entrench,Rarity::uncommon,Type::skill,Color::red,Target::self,2,0,2,0){}
    ~Entrench()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetCost(1, for_preview);
    }
private:
};   
}
} // namespace Card
