#ifndef GAME_OBJECT_CHARACTER_MONSTER_SNEAKYGREMLIN_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_SNEAKYGREMLIN_HPP
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class SneakyGremlinAction
{
    Puncture
};
class SneakyGremlin final:public Monsters
{
public:
    SneakyGremlin(float offsetX,float offsetY);
    ~SneakyGremlin()override=default;
    void Action(SneakyGremlinAction action_type);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    
    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float WIDTH=150.0F*Setting::SCALE,
                        HIGHT=200.0F*Setting::SCALE;
    static constexpr int MAX_HP=14,
                        MIN_HP=10,
                        DAMAGE=9;
    static constexpr float HPBarWidth=WIDTH*0.8F;
};
}
#endif