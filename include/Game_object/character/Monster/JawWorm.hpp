#ifndef GAME_OBJECT_CHARACTER_MONSTER_JaWWORM
#define GAME_OBJECT_CHARACTER_MONSTER_JAWWORM
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class JawWormAction
{
    Chomp,
    Thrash,
    Bellow
};
class JawWorm final:public Monsters
{
public:
    JawWorm(float offsetX,float offsetY);
    ~JawWorm()override=default;
    void Action(JawWormAction action_type);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static const std::shared_ptr<Draw::ReTexture> &img;                    
    static constexpr int WIDTH=260.0F*Setting::SCALE,
                         HIGHT=170.0F*Setting::SCALE;
    static constexpr int MAX_HP=44,
                         MIN_HP=40,
                         DAMAGE=12;
    static constexpr int HPBarWidth=WIDTH*0.8F;
};
}
#endif