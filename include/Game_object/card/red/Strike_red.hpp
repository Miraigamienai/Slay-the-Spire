#pragma once

#include "Game_object/interface/CardPrototype.hpp"//base
#include "RUtil/All_Image.hpp"//AtlasRegionID

namespace Card{
namespace Red{
class Strike_red final:public Interface::CardPrototype<Strike_red>
{
public:
    Strike_red():Interface::CardPrototype<Strike_red>(RUtil::AtlasRegionID::_red_attack_strike,Rarity::basic,Type::attack,Color::red,Target::enemy,1,6,0,0){}

    ~Strike_red()override=default;
    void Use(Dungeon::Dungeon_shared &dungeon_shared,const Monster::Monster_group &room_monsters,const std::shared_ptr<Monster::Monsters> &target_monster)override;
    void Upgrade()override{
        SetDamage(9);
        upgraded=true;
    }
private:

};   
}
} // namespace Card
