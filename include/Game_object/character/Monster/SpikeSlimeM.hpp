#ifndef GAME_OBJECT_CHARACTER_MONSTER_SPIKESLIMEM
#define GAME_OBJECT_CHARACTER_MONSTER_SPIKESLIMEM
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class SpikeSlimeMAction
{
    FlameTackle,
    Lick
};
class SpikeSlimeM final:public Monsters
{
public:
    SpikeSlimeM(float offsetX,float offsetY);
    ~SpikeSlimeM()override=default;
    void Action(SpikeSlimeMAction action_type);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr int WIDTH=170.0F*Setting::SCALE,
                         HIGHT=130.0F*Setting::SCALE;
    static constexpr int MAX_HP=32,
                         MIN_HP=28,
                         DAMAGE=8;
    static constexpr int HPBarWidth=WIDTH*0.8F;
};
}
#endif