#ifndef GAME_OBJECT_CHARACTER_MONSTER_LOOTER
#define GAME_OBJECT_CHARACTER_MONSTER_LOOTER
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class LooterAction
{
    Mug,
    Lunge,
    SmokeBomb,
    Escape
};
class Looter final:public Monsters
{
public:
    Looter(float offsetX,float offsetY);
    ~Looter()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static const std::shared_ptr<Draw::ReTexture> &img;                    
    static constexpr int WIDTH=260.0F*Setting::SCALE,
                         HIGHT=170.0F*Setting::SCALE;
    static constexpr int MAX_HP=48,
                         MIN_HP=44,
                         DAMAGE=10;
    static constexpr int HPBarWidth=WIDTH*0.8F;
};
}
#endif