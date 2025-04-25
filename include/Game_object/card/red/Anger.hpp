#pragma once

#include "Game_object/interface/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID

namespace Card{
namespace Red{
class Anger final:public Interface::CardPrototype<Anger>
{
public:
    Anger():CardPrototype<Anger>(RUtil::AtlasRegionID::_red_attack_anger,Rarity::common,Type::attack,Color::red,Target::enemy,0){}
    ~Anger()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared,const Monster::Monster_group &room_monsters,const std::shared_ptr<Monster::Monsters> &hovered_monster)override;
private:
};   
}
} // namespace Card
