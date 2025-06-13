#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Shrug_it_off final:public Abstraction::CardPrototype<Shrug_it_off>
{
public:
    Shrug_it_off():CardPrototype<Shrug_it_off>(RUtil::AtlasRegionID::_red_skill_shrug_it_off,RUtil::Cards_Text_ID::Shrug_It_Off,Rarity::common,Type::skill,Color::red,Target::self,1,0,8,0){}
    ~Shrug_it_off()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetBlock(11, for_preview);   
    }
};   
}
} // namespace Card
