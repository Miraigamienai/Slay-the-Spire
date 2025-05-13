#ifndef GAME_OBJECT_CHARACTER_MONSTER_SPIKESLIMEM
#define GAME_OBJECT_CHARACTER_MONSTER_SPIKESLIMEM
#include <random>
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class SpikeSlimeMAction
{
    FlameTackle,
    Lick,
    None
};
class SpikeSlimeM final:public Monsters
{
public:
    SpikeSlimeM(float offsetX,float offsetY);
    ~SpikeSlimeM()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr int WIDTH=170.0F*Setting::SCALE,
                         HIGHT=130.0F*Setting::SCALE;
    static constexpr int MAX_HP=32,
                         MIN_HP=28,
                         FLAME_TACKLE_DAMAGE=8;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    Monster::SpikeSlimeMAction currentAction=Monster::SpikeSlimeMAction::None,
                               lastAction=Monster::SpikeSlimeMAction::None;
    static constexpr float ActionProbability[2]={30.0F,70.0F};
    int ActionCount=0;
    static std::discrete_distribution<int> dist;
};
}
#endif