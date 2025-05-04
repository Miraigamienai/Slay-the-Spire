#ifndef GAME_OBJECT_CHARACTER_MONSTER_SPIKESLIMES
#define GAME_OBJECT_CHARACTER_MONSTER_SPIKESLIMES
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class SpikeSlimeSAction
{
    Tackle
};
class SpikeSlimeS final:public Monsters
{
public:
    SpikeSlimeS(float offsetX,float offsetY);
    ~SpikeSlimeS()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr int WIDTH=130.0F*Setting::SCALE,
                         HIGHT=100.0F*Setting::SCALE;
    static constexpr int MAX_HP=14,
                         MIN_HP=10,
                         DAMAGE=5;
    static constexpr int HPBarWidth=WIDTH*0.8F;
};
}
#endif