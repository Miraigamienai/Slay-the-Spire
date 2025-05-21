#ifndef GAME_OBJECT_CHARACTER_MONSTER__GREENLOUSE_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_GREENLOUSE_HPP
#include <random>
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class GreenLouseAction
{
    Bite,
    SpitWeb,
    None
};
class GreenLouse final:public Monsters
{
public:
    GreenLouse(float offsetX,float offsetY);
    ~GreenLouse()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    int m_damage=0;
    static constexpr int WIDTH=180.0F*Setting::SCALE,
                         HIGHT=140.0F*Setting::SCALE;
    static constexpr int MAX_HP=17,
                         MIN_HP=11,
                         MIN_DAMAGE=5,
                         MAX_DAMAGE=7;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    Monster::GreenLouseAction currentAction=Monster::GreenLouseAction::None,
                               lastAction=Monster::GreenLouseAction::None;
    static constexpr float ActionProbability[2]={75.0F,25.0F};
    int ActionCount=0;
    static std::discrete_distribution<int> dist;
};
}
#endif