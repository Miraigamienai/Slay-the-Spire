#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/Damage_info.hpp"
#include "RUtil/Random.hpp"
namespace Monster
{
    Monsters::Monsters(float x, float y, float width, float height) : Characters(x, y, width, height) {}

    void Monsters::damage(const Damage_info& damage_info){
        if(current_Block>damage_info.dmg){
        current_Block-=damage_info.dmg;
        return;
    }
    else if (current_Block){
        current_Block=0;
        current_HP-=damage_info.dmg-current_Block;
    }
    else{
        current_HP-=damage_info.dmg;
    }
}
    void Monsters::setHP(int min,int max){
        this->max_HP=max-int(RUtil::Random::GetRandomFloat(0.0F,max-min+1));
        this->current_HP=max_HP;
    } // namespace Monster
    void Monsters::setBlock(int num){
        this->current_Block=num;
    }

} // namespace Monster