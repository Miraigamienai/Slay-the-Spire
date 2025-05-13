#ifndef GAME_OBJECT_CHARACTER_MONSTER_SPIKESLIMEL
#define GAME_OBJECT_CHARACTER_MONSTER_SPIKESLIMEL
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class SpikeSlimeLAction
{
    FlameTackle,
    Lick,
    Split,
    None
};
class SpikeSlimeL final:public Monsters
{
public:
    SpikeSlimeL(float offsetX,float offsetY);
    ~SpikeSlimeL()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr int WIDTH=300.0F*Setting::SCALE,
                         HIGHT=180.0F*Setting::SCALE;
    static constexpr int MAX_HP=70,
                         MIN_HP=64,
                         FLAME_TACKLE_DAMAGE=16;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    Monster::SpikeSlimeLAction currentAction=Monster::SpikeSlimeLAction::None,
                               lastAction=Monster::SpikeSlimeLAction::None;
    static constexpr float ActionProbability[2]={30.0F,70.0F};
    int ActionCount=0;
};
}
#endif