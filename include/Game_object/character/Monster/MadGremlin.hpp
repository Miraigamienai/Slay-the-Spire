#ifndef GAME_OBJECT_CHARACTER_MONSTER_MADGREMLIN_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_MADGREMLIN_HPP
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class MadGremlinAction
{
    Scratch
};
class MadGremlin final:public Monsters
{
public:
    MadGremlin(float offsetX,float offsetY);
    ~MadGremlin()override=default;
    void Action(MadGremlinAction action_type);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    
    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float WIDTH=150.0F*Setting::SCALE,
                        HIGHT=200.0F*Setting::SCALE;
    static constexpr int MAX_HP=20,
                        MIN_HP=24,
                        DAMAGE=4;
    static constexpr float HPBarWidth=WIDTH*0.8F;
};
}
#endif