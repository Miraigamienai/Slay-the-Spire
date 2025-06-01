#ifndef GAME_OBJECT_CHARACTER_MONSTER_ACIDSLIMEM
#define GAME_OBJECT_CHARACTER_MONSTER_ACIDSLIMEM
#include <random>
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
    enum class AcidSlimeMAction
    {
        CorrosiveSpit,
        Lick,
        Tackle,
        None
    };
class AcidSlimeM final:public Monsters
{
public:
    AcidSlimeM(float offsetX, float offsetY);
    ~AcidSlimeM()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static constexpr int WIDTH=170.0F*Setting::SCALE,
                         HEIGHT=130.0F*Setting::SCALE;
    static constexpr int MAX_HP=32,
                         MIN_HP=28,
                         TACKLE_DAMAGE=10,
                         CORROSIVE_SPIT_DAMAGE=7;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    Monster::AcidSlimeMAction currentAction=Monster::AcidSlimeMAction::None;
    static constexpr float ActionProbability[3]={30.0F,40.0F,30.0F};
    static std::discrete_distribution<int> dist;
};
}
#endif