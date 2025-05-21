#ifndef GAME_OBJECT_CHARACTER_MONSTER_RED_SLAVER_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_RED_SLAVER_HPP
#include <random>
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class RedSlaverAction
{
    Stab,
    Scrape,
    Entangle,
    None
};
class RedSlaver final:public Monsters
{
public:
    RedSlaver(float offsetX,float offsetY);
    ~RedSlaver()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static constexpr int WIDTH=170.0F*Setting::SCALE,
                         HIGHT=230.0F*Setting::SCALE;
    static constexpr int MAX_HP=50,
                         MIN_HP=46,
                         STAB_DAMAGE=13,
                         SCRAPE_DAMAGE=8;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    bool isFirstAction=true;
    bool EntangleIsUsed=false;
    Monster::RedSlaverAction currentAction=Monster::RedSlaverAction::None,
                             lastAction=Monster::RedSlaverAction::None;
    static constexpr float ActionProbabilityAfterEntangle[2]={45.0F,55.0F};
    int ActionCount=0;
    static std::discrete_distribution<int> dist;
};
}
#endif