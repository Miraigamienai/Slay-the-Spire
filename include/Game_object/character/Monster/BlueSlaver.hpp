#ifndef GAME_OBJECT_CHARACTER_MONSTER_BLUE_SLAVER_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_BLUE_SLAVER_HPP
#include <random>
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
    enum class BlueSlaverAction
    {
        Stab,
        Rake,
        None
    };
class BlueSlaver final:public Monsters
{
public:
    BlueSlaver(float offsetX,float offsetY);
    ~BlueSlaver ()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static constexpr int WIDTH=320.0F*Setting::SCALE,
                         HIGHT=230.0F*Setting::SCALE;
    static constexpr int MAX_HP=50,
                         MIN_HP=46,
                         STAB_DAMAGE=12,
                         RAKE_DAMAGE=7;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    Monster::BlueSlaverAction currentAction=Monster::BlueSlaverAction::None,
                               lastAction=Monster::BlueSlaverAction::None;
    static constexpr float ActionProbability[2]={60.0F,40.0F};
    int ActionCount=0;
    static std::discrete_distribution<int> dist;
};
}
#endif