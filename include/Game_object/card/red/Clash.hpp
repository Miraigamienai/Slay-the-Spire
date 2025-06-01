#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Red{
class Clash final:public Abstraction::CardPrototype<Clash>
{
public:
    Clash():CardPrototype<Clash>(RUtil::AtlasRegionID::_red_attack_clash,RUtil::Cards_Text_ID::Clash,Rarity::common,Type::attack,Color::red,Target::enemy,0,14,0,0){}
    ~Clash()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetDamage(18, for_preview);
    }
    bool CanUse(const Dungeon::Dungeon_shared &dungeon_shared)const override;
private:
};   
}
} // namespace Card