#pragma once

#include "Game_object/interface/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID

namespace Card{
namespace Red{
class Strike_red final:public Interface::CardPrototype<Strike_red>
{
public:
    Strike_red():Interface::CardPrototype<Strike_red>(RUtil::AtlasRegionID::_red_attack_strike,Rarity::basic,Type::attack,Color::red,Target::enemy,1){}

    ~Strike_red()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared,const Monster::Monsters &room_monsters)override;
private:

};   
}
} // namespace Card
