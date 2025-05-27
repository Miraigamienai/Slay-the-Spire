#pragma once

#include "Game_object/interface/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Anger final:public Interface::CardPrototype<Anger>
{
public:
    Anger():CardPrototype<Anger>(RUtil::AtlasRegionID::_red_attack_anger,RUtil::Cards_Text_ID::Anger,Rarity::common,Type::attack,Color::red,Target::enemy,0,6,0,0){}
    ~Anger()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(8, for_preview);
    }
private:
};   
}
} // namespace Card
