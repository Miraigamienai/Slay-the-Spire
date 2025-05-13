#ifndef GAME_OBJECT_CHARACTER_MONSTER_REDLOUSE_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_REDLOUSE_HPP
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class RedLouseAction
{
    Bite,
    Grow,
    None
};
class RedLouse final:public Monsters
{
public:
    RedLouse(float offsetX,float offsetY);
    ~RedLouse()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static const std::shared_ptr<Draw::ReTexture> &img;
    int m_damage=0;
    static constexpr int WIDTH=180.0F*Setting::SCALE,
                         HIGHT=140.0F*Setting::SCALE;
    static constexpr int MAX_HP=15,
                         MIN_HP=10,
                         MIN_DAMAGE=5,
                         MAX_DAMAGE=7;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    Monster::RedLouseAction currentAction=Monster::RedLouseAction::None,
                               lastAction=Monster::RedLouseAction::None;
    static constexpr float ActionProbability[2]={75.0F,25.0F};
    int ActionCount=0;
};
}
#endif