#ifndef GAME_OBJECT_CHARACTER_MONSTER_GREMLINNOB
#define GAME_OBJECT_CHARACTER_MONSTER_GREMLINNOB
#include <random>
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class GremlinNobAction
{
    Bellow,
    Rush,
    SkullBash,
    None
};
class GremlinNob final:public Monsters
{
public:
    GremlinNob(float offsetX,float offsetY);
    ~GremlinNob()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:                 
    static constexpr int WIDTH=260.0F*Setting::SCALE,
                         HIGHT=170.0F*Setting::SCALE;
    static constexpr int MAX_HP=86,
                         MIN_HP=82,
                         SKULL_BASH_DAMAGE=6,
                         SKULL_BASH_VULNERABLE=2,
                         RUSH_DAMAGE=14,
                         BELLOWS_STRENGTH=2;
                         
    static constexpr int HPBarWidth=WIDTH*0.8F;
    Monster::GremlinNobAction currentAction=Monster::GremlinNobAction::None,
                           lastAction=Monster::GremlinNobAction::None;
    static constexpr float ActionProbability[3]={25.0F,30.0F,45.0F};
    int ActionCount=0;
    static std::discrete_distribution<int> dist;
};
}
#endif