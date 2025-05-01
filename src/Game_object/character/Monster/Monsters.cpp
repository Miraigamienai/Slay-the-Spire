#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/Damage_info.hpp"
#include "RUtil/Random.hpp"
namespace Monster
{
    Monsters::Monsters(float x, float y, float width, float height,float HPBarWidth) : Characters(x, y, width, height ,HPBarWidth) {
        KindOfCharacter=Character::KindOfCharacter::MONSTER;
    }

    void Monsters::damage(const Damage_info& damage_info){
        if(current_Block>damage_info.dmg){
            current_Block-=damage_info.dmg;
            useStaggerAnimation();
            return;
        }
        else if (current_Block){
            current_Block=0;
            current_HP-=damage_info.dmg-current_Block;
        }
        else if (current_HP){
            if(current_HP>damage_info.dmg){
                current_HP-=damage_info.dmg;
            }
            else if (current_HP<=damage_info.dmg){
                current_HP=0;
            }
        }
        useStaggerAnimation();
    }
    void Monsters::setHP(int min,int max){
        this->max_HP=max-int(RUtil::Random::GetRandomFloat(0.0F,max-min+1));
        this->current_HP=max_HP;
    } // namespace Monster
    void Monsters::setBlock(int num){
        this->current_Block=num;
    }

} // namespace Monster