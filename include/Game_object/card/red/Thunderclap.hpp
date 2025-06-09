// #pragma once

// #include "Game_object/abstraction/CardPrototype.hpp"//base
// #include "RUtil/All_Image.hpp"//AtlasRegionID
// #include "RUtil/Cards_Text_Reader.hpp"//Cards_Text_ID

// namespace Card{
// namespace Red{
// class Thunderclap final:public Abstraction::CardPrototype<Thunderclap>
// {
// public:
//     Thunderclap():Abstraction::CardPrototype<Thunderclap>(RUtil::AtlasRegionID::_red_attack_thunder_clap,RUtil::Cards_Text_ID::Thunderclap,Rarity::common,Type::attack,Color::red,Target::enemy,1,4,0,1){
//         this->exhaust=true;
//     }
//     ~Thunderclap()override=default;
//     void Use(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Monster::Monsters> &target_monster)override;
//     void Upgrade(bool for_preview)override{
//         SetMagicNum(7, for_preview);
//     }
// };   
// }
// } // namespace Card
