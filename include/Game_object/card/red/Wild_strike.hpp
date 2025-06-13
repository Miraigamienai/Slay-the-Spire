#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Wild_strike final:public Abstraction::CardPrototype<Wild_strike>
{
public:
    Wild_strike():Abstraction::CardPrototype<Wild_strike>(RUtil::AtlasRegionID::_red_attack_wild_strike,RUtil::Cards_Text_ID::Wild_Strike,Rarity::common,Type::attack,Color::red,Target::enemy,1,12,0,0){}

    ~Wild_strike()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(17, for_preview);
    }
};
}
} // namespace Card
