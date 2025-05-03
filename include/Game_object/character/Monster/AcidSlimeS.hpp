#ifndef GAME_OBJECT_CHARACTER_MONSTER_ACIDSLIMES
#define GAME_OBJECT_CHARACTER_MONSTER_ACIDSLIMES
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class AcidSlimeSAction
{
    Lick,
    Tackle
};
class AcidSlimeS final:public Monsters
{
public:
    AcidSlimeS(float offsetX,float offsetY);
    ~AcidSlimeS()override=default;
    void Action(AcidSlimeSAction action_type);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr int WIDTH=130.0F*Setting::SCALE,
                         HIGHT=100.0F*Setting::SCALE;
    static constexpr int MAX_HP=12,
                         MIN_HP=8,
                         DAMAGE=3;
    static constexpr int HPBarWidth=WIDTH*0.8F;
};
}
#endif