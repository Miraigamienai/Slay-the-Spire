#pragma once

#include "Game_object/abstraction/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID
#include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

namespace Card{
namespace Status{
class Burn final:public Abstraction::CardPrototype<Burn>
{
public:
    Burn():Abstraction::CardPrototype<Burn>(RUtil::AtlasRegionID::_status_burn, RUtil::Cards_Text_ID::Burn, Rarity::common, Type::status, Color::colorless, Target::none, -1, 0, 0, 2){}
    ~Burn()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade(bool for_preview)override{
        SetMagicNum(4, for_preview);
    }
    bool CanUse(const Dungeon::Dungeon_shared &/* dungeon_shared */)const override{return false;}
    void OnEndOfTurn(Dungeon::Dungeon_shared &dungeon_shared)override;
};   
}
} // namespace Card
