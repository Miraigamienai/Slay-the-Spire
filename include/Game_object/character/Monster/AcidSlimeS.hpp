#ifndef GAME_OBJECT_CHARACTER_MONSTER_ACIDSLIMES
#define GAME_OBJECT_CHARACTER_MONSTER_ACIDSLIMES
#include <random>
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class AcidSlimeSAction
{
    Lick,
    Tackle,
    None
};
class AcidSlimeS final:public Monsters
{
public:
    AcidSlimeS(float offsetX,float offsetY);
    ~AcidSlimeS()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static constexpr int WIDTH=130.0F*Setting::SCALE,
                         HIGHT=100.0F*Setting::SCALE;
    static constexpr int MAX_HP=12,
                         MIN_HP=8,
                         TACKLE_DAMAGE=3;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    AcidSlimeSAction currentAction=Monster::AcidSlimeSAction::None;
    static constexpr float ActionProbability[2]={50.0F,50.0F};
    static std::discrete_distribution<int> dist;
};
}
#endif