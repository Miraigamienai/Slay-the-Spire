#pragma once

#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class JawWormAction
{
    Chomp,
    Thrash,
    Bellow,
    None
};
class JawWorm final:public Monsters
{
public:
    JawWorm(float offsetX,float offsetY);
    ~JawWorm()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(const Power::Power_group &player_powers) override;
private:
    static constexpr int WIDTH=260.0F*Setting::SCALE,
                         HIGHT=170.0F*Setting::SCALE;
    static constexpr int MAX_HP=44,
                         MIN_HP=40,
                         CHOMP_DAMAGE=11,
                         THRASH_DAMAGE=7,
                         THRASH_BLOCK=5,
                         BELLOWS_STRENGTH=3,
                         BELLOWS_BLOCK=6;
    static constexpr float ActionProbability[3]={25.0F,30.0F,45.0F};
    int ActionCount=0;
    static std::discrete_distribution<int> dist;
};
}